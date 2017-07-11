#pragma once
#include "algo/util/pre_compiled_header.h"
#include <memory>

namespace util {
    /**
     * @brief 
     *
     * @tparam Base
     * @tparam Derived
     */
    template <typename Base, typename Derived>
    class MixIn : public Base {
    private:
        /**
         * @brief 
         */
        typedef MixIn<Base, Derived> self_type;
        bool doEqual(const Base& o) const {
            const Derived* sub1 = dynamic_cast<const Derived*>(this);
            const Derived* sub2 = dynamic_cast<const Derived*>(&o);
            return sub1 != 0 && sub2 != 0 && sub1 == sub2;
        }
        Base* doClone() const {
            const Derived* sub = dynamic_cast<const Derived*>(this);
            return new Derived(*sub);
        }
    };
}
