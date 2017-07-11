/**
 * @file ILineSearcher.h
 * @brief 
 * @author i05nagai
 * @version 0.0.1
 * @date 2016-07-20
 */

#pragma once
#include <boost/numeric/ublas/vector.hpp>

namespace algo { namespace qn {
    namespace ublas = boost::numeric::ublas;

    class ILineSearcher : public util::Object<ILineSearcher> {
    //private typedef
    private:
    //public typedef
    public:
    //public function
    public:
        virtual ~ILineSearcher() {}
        /**
         * @brief solve $\\mathrm{argimin}_{\\alpha}(x + \\alpha p)$
         *
         * @param p 
         * @param x
         *
         * @return $\\mathrm{argmin}_{\\alpha}(x + \\alpha p)$
         */
        ublas::vector<double> operator()(
            const ublas::vector<double>& p,
            const ublas::vector<double>& x);
    //private function
    private:
        virtual ublas::vector<double> doOperatorParenthesis(
            const ublas::vector<double>& p,
            const ublas::vector<double>& x) = 0;
    //private members
    private:
    }; // class ILineSearcher {
} } // namespace algo { namespace qn {
