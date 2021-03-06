#pragma once

#include <set>
#include <string>
#include <tuple>
#include <utility>

#include "tcframe/util.hpp"

using std::move;
using std::set;
using std::string;
using std::tie;

namespace tcframe {

struct TestCase {
    friend class TestCaseBuilder;

private:
    string id_;
    optional<string> description_;
    set<int> subtaskIds_;
    TestCaseData* data_;

public:
    const string& id() const {
        return id_;
    }

    const optional<string>& description() const {
        return description_;
    }

    const set<int>& subtaskIds() const {
        return subtaskIds_;
    }

    TestCaseData* data() const {
        return data_;
    }

    bool operator==(const TestCase& o) const {
        if (tie(id_, description_, subtaskIds_) != tie(o.id_, o.description_, o.subtaskIds_)) {
            return false;
        }
        if ((data_ == nullptr) != (o.data_ == nullptr)) {
            return false;
        }
        return data_ == nullptr || data_->equals(o.data_);
    }
};

class TestCaseBuilder {
private:
    TestCase subject_;

public:
    TestCaseBuilder& setId(string id) {
        subject_.id_ = id;
        return *this;
    }

    TestCaseBuilder& setDescription(string description) {
        subject_.description_ = description;
        return *this;
    }

    TestCaseBuilder& setSubtaskIds(set<int> subtaskIds) {
        subject_.subtaskIds_ = subtaskIds;
        return *this;
    }

    TestCaseBuilder& setData(TestCaseData* data) {
        subject_.data_ = data;
        return *this;
    }

    TestCase build() {
        return move(subject_);
    }
};

}
