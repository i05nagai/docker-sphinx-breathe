#include "algo/qn/pre_compiled_header.h"
#include "algo/qn/DavidonFeltcherPowell.h"
#include "algo/qn/ILineSearcher.h"
#include "algo/qn/util.h"
#include "algo/qn/detail/helper_function.hpp"
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <memory>

namespace algo { namespace qn {
    namespace ublas = boost::numeric::ublas;

    template <typename T>
    DavidonFeltcherPowell<T>::DavidonFeltcherPowell(
        const double epsilon, 
        const std::size_t maxIteration)
    : _epsilon(epsilon), _maxIteration(maxIteration)
    {
    }

    template <typename T>
    ublas::vector<double> DavidonFeltcherPowell<T>::doOperatorParenthesis(
        const ublas::vector<double>& x0,
        const function_type& f,
        const std::shared_ptr<ILineSearcher> searcher)
    {
        //initialize
        ublas::vector<double> x1 = x0;
        ublas::matrix<double> H 
            = algo::qn::initilizeQuasiNewtonInverseHessian(x0.size());

        for (std::size_t i = 0; i < _maxIteration; ++i) {
            const auto& gradient = detail::calculateDerivative(f, x1);
            const auto& p = -ublas::prod(H, gradient);
            const auto& x2 = (*searcher)(p, x1);
            const auto& df1 = detail::calculateDerivative(f, x1);
            const auto& df2 = detail::calculateDerivative(f, x2);
            H = this->calculateInverseHessian(x1, x2, df1, df2, H);

            if (this->isConverge(x1, x2)) {
                return x2;
            }

            //preparation for next step
            x1 = x2;
        }

        return x1;
    }

    template <typename T>
    ublas::matrix<double> DavidonFeltcherPowell<T>::calculateInverseHessian(
        const ublas::vector<double>& x1,
        const ublas::vector<double>& x2,
        const ublas::vector<double>& df1,
        const ublas::vector<double>& df2,
        const ublas::matrix<double>& H)
    {
        assert(H.size1() == H.size2());

        const auto& dx = x2 - x1;
        const auto& y = df2 - df1;
        const auto& Hy = ublas::prod<ublas::vector<double> >(H, y);
        const auto& Hyy = ublas::outer_prod(Hy, y);

        const auto& term1 = ublas::outer_prod(dx, dx) / ublas::inner_prod(dx, y);
        const auto& term2 = ublas::prod(Hyy, H) / ublas::inner_prod(y, Hy);

        return H + term1 - term2;
    }

    template <typename T>
    bool DavidonFeltcherPowell<T>::isConverge(
        const ublas::vector<double>& x1, 
        const ublas::vector<double>& x2)
    {
        const double error = algo::qn::calculateDistanceNormL2(x1, x2);
        if (error < _epsilon) {
            return true;
        } else {
            return false;
        }
    }

} } // namespace algo { namespace qn {

namespace algo { namespace qn {
    namespace ublas = boost::numeric::ublas;
    typedef std::function<double (
        const ublas::vector<double>& x)> double_function_type;

    template
    DavidonFeltcherPowell<double>::DavidonFeltcherPowell(
        const double epsilon, 
        const std::size_t maxIteration);
    template
    ublas::vector<double> 
    DavidonFeltcherPowell<double>::doOperatorParenthesis(
        const ublas::vector<double>& x0,
        const double_function_type& f,
        const std::shared_ptr<ILineSearcher> searcher);
    template
    ublas::matrix<double> 
    DavidonFeltcherPowell<double>::calculateInverseHessian(
        const ublas::vector<double>& x1,
        const ublas::vector<double>& x2,
        const ublas::vector<double>& df1,
        const ublas::vector<double>& df2,
        const ublas::matrix<double>& H);
    template
    bool DavidonFeltcherPowell<double>::isConverge(
        const ublas::vector<double>& x1, 
        const ublas::vector<double>& x2);
} } // namespace algo { namespace qn {
