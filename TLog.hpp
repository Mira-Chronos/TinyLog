#ifndef __TINY_LOG__
#define __TINY_LOG__


#include <fstream>
#include <mutex>
#include <sstream>

#define LOG_CR "(CR): "
#define LOG_EE "(EE): "
#define LOG_WW "(WW): "
#define LOG_DD "(DD): "
#define LOG_II "(II): "
#define LOG_OR "      "

/**
 * \enum LOG_TYPE
 * \brief Types de log
 */
enum class LOG_TYPE : char {
	L_CRITICAL,
	L_ERROR,
	L_WARNING,
	L_DEBUG,
	L_INFO,
	L_OTHER
};

class TLog {
public:
	TLog(TLog const&) = delete;
	TLog& operator=(TLog const&) = delete;
	~TLog();

    static TLog* get() {
    	static TLog instance;
    	return &instance;
    }

    static TLog& ss() {
    	return * get();
    }

    // surcharges
    TLog& operator<<(LOG_TYPE type);
    TLog& operator<<(const std::string& msg);
    TLog& operator<<(const char* msg);

	/*!
	*  \brief Ecrit une string dans un log
	*  \param type : enum du type (optionnel, INFO par defaut)
	*/
	void write(const std::string& texte, const LOG_TYPE& type = LOG_TYPE::L_INFO);

	/*!
	*  \brief Ecrit un flux dans un log
	*  \param type : enum du type (optionnel, INFO par defaut)
	*/
	inline void write(const std::ostringstream& texte, const LOG_TYPE& type = LOG_TYPE::L_INFO) {
		write(texte.str(), type);
	}

	/*!
	*  \brief Insère une marque dans le log
	*/
	void mark();

	/*!
	*  \brief Configure l'état du Debug
	*  \param state : état du Debug souhaité (true ou false)
	*/
	void debugOnConsole(bool state) {
		displayOnConsole = state;
	}

	/*!
	*  \brief Configure l'état du Debug
	*  \param state : état du Debug souhaité (true ou false)
	*/
	void debugWithTimer(bool state) {
		displayTimer = state;
	}

	/*!
	*  \brief Ouvre les fichiers de log
	*  \param LogfileName : nom du fichier de log
	*/
	void open(const std::string& LogfileName);
	void close();

private:
	TLog();

	std::mutex writeMutex;
	std::ofstream Logfile;

	void writeConsole(const std::string&, const LOG_TYPE&);
	std::string getTimestamp();
	bool displayOnConsole = false;
	bool displayTimer = false;
	LOG_TYPE currentType;
};


#endif
