#include "algo/qn/pre_compiled_header.h"
#include "algo/qn/BroydenFletcherGoldfarbShanno.h"
#include "algo/qn/ILineSearcher.h"
#include "algo/qn/util.h"
#include "algo/qn/detail/helper_function.hpp"
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <memory>

namespace algo { namespace qn {
    namespace ublas = boost::numeric::ublas;

    template <typename T>
    BroydenFletcherGoldfarbShanno<T>::BroydenFletcherGoldfarbShanno(
        const double epsilon,
        const std::size_t maxIteration)
    : _epsilon(epsilon), _maxIteration(maxIteration)
    {
    }

    template <typename T>
    ublas::vector<double> BroydenFletcherGoldfarbShanno<T>::doOperatorParenthesis(
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
    ublas::matrix<double> 
    BroydenFletcherGoldfarbShanno<T>::calculateInverseHessian(
        const ublas::vector<double>& x1,
        const ublas::vector<double>& x2,
        const ublas::vector<double>& df1,
        const ublas::vector<double>& df2,
        const ublas::matrix<double>& H)
    {
        assert(H.size1() == H.size2());
        
        const auto& dx = x2 - x1;
        const auto& y = df2 - df1;
        const double scalar1 = ublas::inner_prod(y, dx);
        const double scalar2 = ublas::inner_prod(y, ublas::prod(H, y));
        const auto& matrix1 = ublas::outer_prod(dx, dx);
        const auto& term1 = ((scalar1 + scalar2) * matrix1) / (scalar1 * scalar1);

        const auto& matrix2 = ublas::outer_prod(y, dx);
        const auto& matrix3 = ublas::prod(H, matrix2);
        const auto& matrix4 = ublas::outer_prod(dx, y);
        const auto& matrix5 = ublas::prod(matrix4, H);
        const auto& term2 = (matrix3 + matrix5) / scalar1;

        return H + term1 - term2;
    }

    template <typename T>
    bool BroydenFletcherGoldfarbShanno<T>::isConverge(
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
    typedef ublas::vector<double> infinitesimal_type;
    typedef ad::dual<infinitesimal_type> dual_type;
    typedef std::function<dual_type (
        const ublas::vector<dual_type>& x)> dual_function_type;
    //double
    template
    BroydenFletcherGoldfarbShanno<double>::BroydenFletcherGoldfarbShanno(
        const double epsilon,
        const std::size_t maxIteration);
    template
    ublas::vector<double> 
    BroydenFletcherGoldfarbShanno<double>::doOperatorParenthesis(
        const ublas::vector<double>& x0,
        const double_function_type& f,
        const std::shared_ptr<ILineSearcher> searcher);
    template
    ublas::matrix<double> 
    BroydenFletcherGoldfarbShanno<double>::calculateInverseHessian(
        const ublas::vector<double>& x1,
        const ublas::vector<double>& x2,
        const ublas::vector<double>& df1,
        const ublas::vector<double>& df2,
        const ublas::matrix<double>& H);
    template
    bool BroydenFletcherGoldfarbShanno<double>::isConverge(
        const ublas::vector<double>& x1, 
        const ublas::vector<double>& x2);
    //dual
    template
    BroydenFletcherGoldfarbShanno<dual_type>::BroydenFletcherGoldfarbShanno(
        const double epsilon,
        const std::size_t maxIteration);
    template
    ublas::vector<double> 
    BroydenFletcherGoldfarbShanno<dual_type>::doOperatorParenthesis(
        const ublas::vector<double>& x0,
        const dual_function_type& f,
        const std::shared_ptr<ILineSearcher> searcher);
    template
    ublas::matrix<double> 
    BroydenFletcherGoldfarbShanno<dual_type>::calculateInverseHessian(
        const ublas::vector<double>& x1,
        const ublas::vector<double>& x2,
        const ublas::vector<double>& df1,
        const ublas::vector<double>& df2,
        const ublas::matrix<double>& H);
    template
    bool BroydenFletcherGoldfarbShanno<dual_type>::isConverge(
        const ublas::vector<double>& x1, 
        const ublas::vector<double>& x2);
} } // namespace algo { namespace qn {
