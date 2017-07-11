#include "algo/qn/pre_compiled_header.h"
#include "algo/qn/util.h"

namespace algo { namespace qn {
    namespace ublas = boost::numeric::ublas;

    ublas::matrix<double> initilizeQuasiNewtonHessian(const std::size_t size)
    {
        return ublas::identity_matrix<double>(size);
    }

    ublas::matrix<double> initilizeQuasiNewtonInverseHessian(
        const std::size_t size)
    {
        return ublas::identity_matrix<double>(size);
    }

    template <typename E>
    double calculateSumOfSquares(const ublas::vector_expression<E>& x)
    {
        double sum = 0.0;
        for (std::size_t i = 0; i < x().size(); ++i) {
            sum += (x()(i) * x()(i));
        }
        return sum;
    }

    double calculateDistanceNormL2(
        const ublas::vector<double>& x1,
        const ublas::vector<double>& x2)
    {
        const double sum = algo::qn::calculateSumOfSquares(x2 - x1);
        return std::sqrt(sum);
    }

    double calculateNormL2(const ublas::vector<double>& x)
    {
        const double sum = algo::qn::calculateSumOfSquares(x);
        return std::sqrt(sum);
    }
} } // namespace algo { namespace qn {

