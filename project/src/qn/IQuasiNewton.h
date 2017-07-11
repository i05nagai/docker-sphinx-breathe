/**
 * @file IQuasiNewton.h
 * @brief 
 * @author i05nagai
 * @version 0.0.1
 * @date 2016-07-20
 */

#pragma once
#include "algo/qn/ILineSearcher.h"
#include "algo/util/util.h"
#include <boost/numeric/ublas/vector.hpp>

namespace algo { namespace qn {
    namespace ublas = boost::numeric::ublas;

    /**
     * @brief 
     */
    template <typename Value>
    class IQuasiNewton : public util::Object<IQuasiNewton<Value> > {
    //private typedef
    private:
    //public typedef
    public:
        typedef std::function<Value (
            const ublas::vector<Value>& x)> function_type;
    //public function
    public:
        virtual ~IQuasiNewton() {}
        /**
         * @brief solve $\\mathrm{argmin}_{x}f(x)
         *
         * @param x0 initial value.
         * @param f objective funciton.
         *
         * @return objective value if it exists.
         */
        ublas::vector<double> operator()(
            const ublas::vector<double>& x0,
            const function_type& f,
            const std::shared_ptr<ILineSearcher> searcher);
    //private function
    private:
        virtual ublas::vector<double> doOperatorParenthesis(
            const ublas::vector<double>& x0,
            const function_type& f,
            const std::shared_ptr<ILineSearcher> searcher) = 0;
    //private members
    private:
    }; // class IQuasiNewton {
} } // namespace algo { namespace qn {
 
