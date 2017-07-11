/**
 * @file utility.h
 * @brief 
 * @author i05nagai
 * @version 0.0.1
 * @date 2016-07-20
 */

#pragma once
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_expression.hpp>

namespace algo { namespace qn {
    namespace ublas = boost::numeric::ublas;
    /**
     * @brief 
     *
     * @param size
     *
     * @return 
     */
    ublas::matrix<double> 
    initilizeQuasiNewtonHessian(const std::size_t size);
    /**
     * @brief 
     *
     * @param size
     *
     * @return 
     */
    ublas::matrix<double> 
    initilizeQuasiNewtonInverseHessian(const std::size_t size);
    /**
     * @brief caculates sum of squares.
     *
     * @tparam E expression.
     * @param x vector.
     *
     * @return sum of squares.
     */
    template <typename E>
    double calculateSumOfSquares(const ublas::vector_expression<E>& x);
    /**
     * @brief calculate distance between x1 and x2.
     *
     * @param x1
     * @param x2
     *
     * @return 
     */
    double calculateDistanceNormL2(
        const ublas::vector<double>& x1,
        const ublas::vector<double>& x2);
    /**
     * @brief calculates euclidean norm.
     *
     * @param x1 point.
     * @param x2 point.
     *
     * @return euclidean norm.
     */
    double calculateNormL2(const ublas::vector<double>& x);
} } // namespace algo { namespace qn {

