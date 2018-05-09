/**
 * gbdt_factory.h
 *
 * @author: huanghui
 *
 */

#ifndef GBDT_FACTORY_H_
#define GBDT_FACTORY_H_

#include <map>
#include <pthread.h>
#include "gbdt_common.h"
#include "gbdt_model.h"

NAMESPACE_GBRANKING_START

class gbdt_factory_t {
    private:
        pthread_rwlock_t _model_mutex;
        std::map<std::string, GbdtModel *> _model_map;
        std::string _dir_name;
        bool _is_loaded;

    private:
        static gbdt_factory_t & _get_instance();
        gbdt_factory_t();

    public:
        pthread_rwlock_t& get_rwlock() {return _model_mutex;};
        static int load_model_from_dir(const std::string & dir_name);
        static int add_model(const std::string & file_name, const char * model_name = NULL);
        static GbdtModel * get_model(const std::string & model_name);
        static void dump();
        ~gbdt_factory_t();

        static int reload_models();
};

NAMESPACE_GBRANKING_END

#endif /* GBDT_FACTORY_H_ */
