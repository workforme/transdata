/**
 * gbdt_factory.cpp
 *
 * @author: huanghui
 *
 */

#include "gbdt_factory.h"
#include "file_utils.h"
#include "string_utils.h"
#include "logger.h"

NAMESPACE_GBRANKING_START

using namespace cmnewslib;

gbdt_factory_t::gbdt_factory_t(): _model_mutex(PTHREAD_RWLOCK_INITIALIZER) {
    _is_loaded = false;
}

gbdt_factory_t::~gbdt_factory_t() {
    std::map<std::string, GbdtModel *>::iterator it = _model_map.begin();
    for (; it != _model_map.end(); it++) {
        delete it->second;
    }
    pthread_rwlock_destroy(&_model_mutex);
}

gbdt_factory_t & gbdt_factory_t::_get_instance() {
    static gbdt_factory_t _instance;
    return _instance;
}

int gbdt_factory_t::load_model_from_dir(const std::string & dir_name) {
    gbdt_factory_t & factory = _get_instance();
    if (factory._is_loaded) {
        return 0;
    }
    std::vector<std::string> file_list = file_utils_t::list_dir(dir_name);
    for (size_t i = 0; i < file_list.size(); i++) {
        std::string & fname = file_list[i];
        if (string_utils_t::endswith(fname, ".model")) {
            LOG_DEBUG("loading file %s ...", fname.c_str());
            if (add_model(fname, NULL) < 0) {
                return -1;
            }
        }
    }

    factory._dir_name = dir_name;
    factory._is_loaded = true;
    return 0;
}

int gbdt_factory_t::add_model(const std::string & file_name, const char * _model_name) {
    int res = 0;
    std::string model_name;
    gbdt_factory_t & factory = _get_instance();

    if (_model_name != NULL) {
        model_name = _model_name;
    } else {
        size_t pos_slash = file_name.find_last_of('/');
        size_t pos_dot = file_name.find_last_of('.');
        size_t start_pos = (pos_slash == std::string::npos ? 0 : pos_slash + 1);
        size_t len = (pos_dot == std::string::npos ? std::string::npos : pos_dot - start_pos);
        model_name = file_name.substr(start_pos, len);
    }

    if (model_name.empty()) {
        LOG_WARN("cannot get model name for [%s]", file_name.c_str());
        return -1;
    }

    if (factory._model_map.find(model_name) != factory._model_map.end()) {
        //LOG_WARN("model [%s] is already loaded in memory", model_name.c_str());
        return -2;
    }


    GbdtModel * p_model = new GbdtModel();
    res = p_model->load(file_name);
    if (res != 0) {
        LOG_WARN("failed to load gbdt model [%s], res=%d", file_name.c_str(), res);
        delete p_model;
        return -3;
    }

    pthread_rwlock_wrlock(&factory.get_rwlock());
    factory._model_map[model_name] = p_model;
    pthread_rwlock_unlock(&factory.get_rwlock());
    LOG_INFO("loaded gbdt model, name=%s", model_name.c_str());

    return res;
}

GbdtModel * gbdt_factory_t::get_model(const std::string & model_name) {
    gbdt_factory_t & factory = _get_instance();
    GbdtModel * res = NULL;
    pthread_rwlock_rdlock(&factory.get_rwlock());
    std::map<std::string, GbdtModel *>::const_iterator it = factory._model_map.find(model_name);
    if (it != factory._model_map.end()) {
        res = it->second;
    }
    pthread_rwlock_unlock(&factory.get_rwlock());
    return res;
}

 void gbdt_factory_t::dump() {
    gbdt_factory_t & factory = _get_instance();
    std::map<std::string, GbdtModel *>::const_iterator it = factory._model_map.begin();
    LOG_DEBUG("***** gbdt_factory_t::dump start *****");
    for (; it != factory._model_map.end(); it++) {
        LOG_DEBUG("model_name=%s, model=%p", it->first.c_str(), it->second);
    }
    LOG_DEBUG("***** gbdt_factory_t::dump end *****");
}

int gbdt_factory_t::reload_models() {
    gbdt_factory_t & factory = _get_instance();

    std::vector<std::string> file_list = file_utils_t::list_dir(factory._dir_name);
    bool has_model_added = false;
    for (size_t i = 0; i < file_list.size(); i++) {
        std::string & fname = file_list[i];
        if (string_utils_t::endswith(fname, ".model")) {
            LOG_DEBUG("loading file %s ...", fname.c_str());
            int res = add_model(fname, NULL);
            if (-2 == res) {
                continue;
            }
            if (res < 0 && res != -2) {
                LOG_ERROR("gbdt model factory update failed");
                return -1;
            }
            has_model_added = true;
        }
    }

    if (has_model_added) {
        LOG_INFO("gbdt model factory update succeeded!");
        return 1;
    } else {
        return 0;
    }
}

NAMESPACE_GBRANKING_END

