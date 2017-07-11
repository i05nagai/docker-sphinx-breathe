/**
 * @file BroydenFletcherGoldfarbShanno.h
 * @brief 
 * @author i05nagai
 * @version 0.0.1
 * @date 2016-07-20
 */

#pragma once
#include "algo/qn/pre_compiled_header.h"
#include "algo/qn/IQuasiNewton.h"
#include "algo/qn/ILineSearcher.h"
#include "algo/qn/util.h"
#include "algo/util/util.h"

namespace algo { namespace qn {
    namespace ublas = boost::numeric::ublas;

    template <typename T>
    class BroydenFletcherGoldfarbShanno 
    : public util::MixIn<IQuasiNewton<T>, BroydenFletcherGoldfarbShanno<T> > {
    //private typedef
    private:
    //public typedef
    public:
        /**
         * @typedef 
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
        BroydenFletcherGoldfarbShanno(
            const double epsilon,
            const std::size_t maxIteration);
    //private function
    private:
        ublas::vector<double> doOperatorParenthesis(
            const ublas::vector<double>& x0,
            const function_type& f,
            const std::shared_ptr<ILineSearcher> searcher);
        /**
         * @brief calculates inverse hessian by follwoing formula:
         * $$
         * B_{k+1}^{-1} := \\left(I - \\frac{dx_{k} y_{k}^{T}}{y_{k}^{T}dx_{k}} \\right) B_{k}^{-1} \\left( I - \\frac{y_{k}dx_{k}^{T}}{y_{k}^{T}dx_{k}}\\right) + \\frac{dx_{k}dx^{T}}{y_{k}^{T}s_{k}}.
         * $$
         * Here $B_{k}$ is $k$-th hessian, $dx_{k} := x_{k+1} - x_{k}$, $I$ is identity matrix, $y_{k} := df_{k+1} - df_{k}.$
         * Following formula is derived from above equation.
         * $$
         * B_{k+1}^{-1} = \\frac{B_{k}^{-1} + (dx_{k}^{T}y_{k} + y_{k}^{T}B_{k}^{-1}y_{k})(dx_{k}dx_{k}^{T})}{(dx_{k}^{T}y_{k})^{2}} - \\frac{B_{k}^{-1}y_{k}dx_{k}^{T} + dx_{k}y_{k}^{T}B_{k}^{-1}}{dx_{k}^{T}y_{k}}.
         * $$
         * @todo check the first equation is correct or not.
         *
         * @param x1 previous value.
         * @param x2 current value.
         * @param df1 
         * @param df2 
         * @param H previous inverse hessian.
         *
         * @return inverse hessian.
         */
        ublas::matrix<double> calculateInverseHessian(
            const ublas::vector<double>& x1,
            const ublas::vector<double>& x2,
            const ublas::vector<double>& df1,
            const ublas::vector<double>& df2,
            const ublas::matrix<double>& H);
        /**
         * @brief Check whether algorithm is converged or not.
         *
         * @param x1 previous value.
         * @param x2 current value.
         *
         * @return true if algorithm is converged.
         */
        bool isConverge(
            const ublas::vector<double>& x1,
            const ublas::vector<double>& x2);
    //private members
    private:
        const double _epsilon;
        const std::size_t _maxIteration;
    }; // class BroydenFletcherGoldfarbShanno : public IQuasiNewton {
} } // namespace algo { namespace qn {

