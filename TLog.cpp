#include "TLog.hpp"
#include <iostream>
#include <exception>
#include <string>
#include <time.h>
#include <iomanip>

// thanks to internet for color !!
// http://stackoverflow.com/questions/1961209/making-some-text-in-printf-appear-in-green-and-red
#define LOG_RESET   "\033[0m"
#define LOG_BLACK   "\033[30m"      /* Black */
#define LOG_RED     "\033[31m"      /* Red */
#define LOG_GREEN   "\033[32m"      /* Green */
#define LOG_YELLOW  "\033[33m"      /* Yellow */
#define LOG_BLUE    "\033[34m"      /* Blue */
#define LOG_MAGENTA "\033[35m"      /* Magenta */
#define LOG_CYAN    "\033[36m"      /* Cyan */
#define LOG_WHITE   "\033[37m"      /* White */
#define LOG_BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define LOG_BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define LOG_BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define LOG_BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define LOG_BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define LOG_BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define LOG_BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define LOG_BOLDWHITE   "\033[1m\033[37m"      /* Bold White */



TLog::TLog()
{}

void TLog::open(const std::string& LogfileName)
{
	Logfile.open(LogfileName, std::ofstream::out | std::ofstream::trunc);
	if (!Logfile.is_open()) {
		std::cerr << "(EE): Couldn't open file log!\n Please check file/directory permissions" << std::endl;
		throw;
	}
}

void TLog::close()
{
    if (Logfile.is_open()) {
		write("EOF", LOG_TYPE::L_OTHER);
	    Logfile.close();
    }
}

TLog::~TLog()
{
	Logfile.close();
}


void TLog::write(const std::string& texte, const LOG_TYPE& type)
{
	writeMutex.lock();
	std::string ligne;

	if (displayOnConsole) {
		writeConsole(texte, type);
	}
	if (!Logfile.is_open()) {
		writeMutex.unlock();
		return;
	}

	if (displayTimer) {
		ligne.append(getTimestamp()+ " ");
	}

	switch(type) {
		case LOG_TYPE::L_CRITICAL :
			ligne.append(LOG_CR);
			break;
		case LOG_TYPE::L_WARNING :
			ligne.append(LOG_WW);
			break;
		case LOG_TYPE::L_ERROR :
			ligne.append(LOG_EE);
			break;
		case LOG_TYPE::L_DEBUG :
			ligne.append(LOG_DD);
			break;
		case LOG_TYPE::L_INFO :
			ligne.append(LOG_II);
			break;
		default :
			ligne.append(LOG_OR);
	}
	ligne.append(texte);
	ligne.append("\r\n");

	Logfile << ligne;
	Logfile.flush();

	writeMutex.unlock();
}

void TLog::mark()
{
	write("=================================================================", LOG_TYPE::L_OTHER);
}

void TLog::writeConsole(const std::string& texte, const LOG_TYPE& type)
{
	std::string ligne;
	switch(type) {
		case LOG_TYPE::L_CRITICAL :
			ligne.append(LOG_BOLDRED);
			ligne.append(LOG_CR);
			ligne.append(LOG_RESET);
			ligne.append(LOG_BOLDRED);
			break;

		case LOG_TYPE::L_WARNING :
			ligne.append(LOG_BOLDYELLOW);
			ligne.append(LOG_WW);
			ligne.append(LOG_RESET);
			ligne.append(LOG_WHITE);
			break;

		case LOG_TYPE::L_ERROR :
			ligne.append(LOG_BOLDRED);
			ligne.append(LOG_EE);
			ligne.append(LOG_RESET);
			ligne.append(LOG_BOLDWHITE);
			break;

		case LOG_TYPE::L_DEBUG :
			ligne.append(LOG_MAGENTA);
			ligne.append(LOG_DD);
			ligne.append(LOG_RESET);
			ligne.append(LOG_WHITE);
			break;

		case LOG_TYPE::L_INFO :
			ligne.append(LOG_BOLDGREEN);
			ligne.append(LOG_II);
			ligne.append(LOG_RESET);
			ligne.append(LOG_WHITE);
			break;

		default :
			ligne.append(LOG_WHITE);
			ligne.append(LOG_OR);
	}

	ligne.append(texte);
	ligne.append(LOG_RESET);
	ligne.append("\r\n");

	if(type == LOG_TYPE::L_ERROR || type == LOG_TYPE::L_WARNING || type == LOG_TYPE::L_CRITICAL) {
		std::cerr << ligne;
	} else {
		std::cout << ligne;
	}

}


std::string TLog::getTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::ostringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}


TLog& TLog::operator<<(LOG_TYPE type) {
    // Stockez le type pour le prochain message, ou gérez-le comme vous le souhaitez
    // Par exemple :
    this->currentType = type;
    return *this;
}

TLog& TLog::operator<<(const std::string& msg) {
    // Écrivez le message avec le type courant
    this->write(msg, currentType); // ou toute autre logique
    return *this;
}

TLog& TLog::operator<<(const char* msg) {
    return (*this) << std::string(msg);
}