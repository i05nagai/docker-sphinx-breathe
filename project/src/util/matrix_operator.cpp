#include "algo/util/matrix_operator.h"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>

namespace algo { namespace util {
    template <typename Value>
    bool invert(
        const boost::numeric::ublas::matrix<Value>& matrix, 
        boost::numeric::ublas::matrix<Value>& inverseMatrix)
    {
        namespace ublas = boost::numeric::ublas;
        //must be square matrix.
        BOOST_UBLAS_CHECK(matrix.size1() == matrix.size2(), ublas::external_logic());
        const std::size_t matrixSize = matrix.size1();

        ublas::matrix<Value> copyMatrix(matrix);
        ublas::permutation_matrix<std::size_t> permutationMatrix(matrixSize);
        int singular = ublas::lu_factorize(copyMatrix, permutationMatrix);
        if (singular != 0) {
            return false;
        }

        inverseMatrix.assign(ublas::identity_matrix<Value>(matrixSize));
        ublas::lu_substitute(copyMatrix, permutationMatrix, inverseMatrix);

        return true;
    } 
} } // namespace algo { namespace util {

namespace algo { namespace util {
    template 
    bool invert(
        const boost::numeric::ublas::matrix<double>& matrix, 
        boost::numeric::ublas::matrix<double>& inverseMatrix);
} } // namespace algo { namespace util {

