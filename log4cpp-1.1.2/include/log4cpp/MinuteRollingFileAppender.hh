/*
 * MinuteRollingFileAppender.hh
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_MINUTEROLLINGFILEAPPENDER_HH
#define _LOG4CPP_MINUTEROLLINGFILEAPPENDER_HH

#include <log4cpp/Portability.hh>
#include <log4cpp/FileAppender.hh>
#include <string>
#include <stdarg.h>

namespace log4cpp {

    /**
       MinuteRollingFileAppender is a FileAppender that rolls over the logfile once
       per x minutes.
       @since 1.1.2-cmcm
    **/
    class LOG4CPP_EXPORT MinuteRollingFileAppender : public FileAppender {
        public:
        MinuteRollingFileAppender(const std::string& name,
                            const std::string& fileName,
                            unsigned int rollingFrequencyInMinute,
                            unsigned int maxFilesToKeep = maxFilesToKeepDefault,
                            bool append = true,
                            mode_t mode = 00644);

        virtual void setMaxFilesToKeep(unsigned int maxFilesToKeep);
        virtual unsigned int getMaxFilesToKeep() const;

        virtual void rollOver();

        static unsigned int maxFilesToKeepDefault;
        protected:
        virtual void _append(const LoggingEvent& event);

        unsigned int _rollingFrequencyInMinute;
        unsigned int _maxFilesToKeep;
        // last log's file creation time (or last modification if appender just created)
        struct tm _logsTime;
    };
}

#endif // _LOG4CPP_MINUTEROLLINGFILEAPPENDER_HH
