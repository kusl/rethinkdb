// Copyright 2010-2013 RethinkDB, all rights reserved.
#ifndef RDB_PROTOCOL_EXPLAIN_HPP_
#define RDB_PROTOCOL_EXPLAIN_HPP_

#include <vector>
#include <memory>

#include "errors.hpp"
#include <boost/optional.hpp>
#include <boost/variant.hpp>

#include "utils.hpp"
#include "containers/counted.hpp"

namespace ql {
class datum_t;
} //namespace ql

class explain_t {
public:
    explain_t(const std::string &description);
    ~explain_t();
    explain_t *new_task(const std::string &description);
    explain_t *new_parallel_task(const std::string &description);
    explain_t *finish_parallel_tasks(
            const std::vector<explain_t *> &tasks,
            const std::string &description);

    void finish();

    counted_t<const ql::datum_t> as_datum() const;

private:
    void as_datum_helper(std::vector<counted_t<const ql::datum_t> > *parent) const;
    counted_t<const ql::datum_t> get_atom() const;

    std::string description_;
    ticks_t start_time_;
    boost::optional<ticks_t> ticks_;
    std::vector<explain_t *> parallel_tasks;
    explain_t *next_task;
};
#endif
