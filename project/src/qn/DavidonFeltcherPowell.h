/**
 * @file DavidonFeltcherPowell.h
 * @brief 
 * @author i05nagai
 * @version 0.0.1
 * @date 2016-07-20
 */

#pragma once
#include "algo/util/util.h"
#include "algo/qn/ILineSearcher.h"
#include "algo/qn/IQuasiNewton.h"

namespace algo { namespace qn {
    namespace ublas = boost::numeric::ublas;

    template <typename T>
    class DavidonFeltcherPowell 
    : public util::MixIn<IQuasiNewton<T>, DavidonFeltcherPowell<T> > {
    //private typedef
    private:
    //public typedef
    public:
        /**
         * @brief 
         */
        typedef std::function<T (
            const ublas::vector<T>& x)> function_type;
    //public function
    public:
        /**
         * @brief 
         *
         * @param epsilon algorithm is converged if error is less 
         *  than epsilon.
         * @param maxIteration algorithm is iterated until 
         *  converged or number of maxInteration.
         */
        DavidonFeltcherPowell(
            const double epsilon, 
            const std::size_t maxIteration);
    //private function
    private:
        /**
         * @brief 
         *
         * @param x0
         * @param f
         * @param gradf
         *
         * @return 
         */
        ublas::vector<double> doOperatorParenthesis(
            const ublas::vector<double>& x0,
            const function_type& f,
            const std::shared_ptr<ILineSearcher> searcher);
        /**
         * @brief 
         *
         * @param x1
         * @param x2
         * @param df1
         * @param df2
         * @param H
         *
         * @return 
         */
        ublas::matrix<double> calculateInverseHessian(
            const ublas::vector<double>& x1,
            const ublas::vector<double>& x2,
            const ublas::vector<double>& df1,
            const ublas::vector<double>& df2,
            const ublas::matrix<double>& H);
        /**
         * @brief 
         *
         * @param x1
         * @param x2
         *
         * @return 
         */
        bool isConverge(
            const ublas::vector<double>& x1, 
            const ublas::vector<double>& x2);
    //private members
    private:
        const double _epsilon;
        const std::size_t _maxIteration;
    }; // class DavidonFeltcherPowell : public IQuasiNewton {
} } // namespace algo { namespace qn {
