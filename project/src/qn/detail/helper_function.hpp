#pragma once
#include "algo/ad/dual.hpp"
#include "algo/ad/util.hpp"

namespace algo { namespace qn { namespace detail {
    template <typename T>
    inline boost::numeric::ublas::vector<double>
    calculateDerivative(
        const std::function<ad::dual<T> (
            const boost::numeric::ublas::vector<ad::dual<T> >& x)>& f,
        const boost::numeric::ublas::vector<ad::dual<T>>& x)
    {
        return f(x).getDerivative();
    }

    template <typename T>
    inline boost::numeric::ublas::vector<double>
    calculateDerivative(
        const std::function<ad::dual<T> (
            const boost::numeric::ublas::vector<ad::dual<T> >& x)>& f,
        const boost::numeric::ublas::vector<double>& x)
    {
        namespace ublas = boost::numeric::ublas;
        typedef ublas::vector<double> infinitesimal_type;
        typedef ad::dual<infinitesimal_type> dual_type;

        ublas::vector<dual_type> dualX = ad::makeVectorDual(x);

        return f(dualX).getDerivative();;
    } 

    inline boost::numeric::ublas::vector<double>
    calculateDerivative(
        const std::function<double (
            const boost::numeric::ublas::vector<double>& x)>& f,
        const boost::numeric::ublas::vector<double>& x)
    {
        namespace ublas = boost::numeric::ublas;

        const double delta = 0.01;
        const std::size_t size = x.size();
        ublas::vector<double> differential(size);

        for (std::size_t i = 0; i < size; ++i) {
            const auto unitVector = ublas::unit_vector<double>(size, i);
            const auto& shockedVector =  unitVector * delta;
            differential(i)
                = (f(x + shockedVector) - f(x - shockedVector)) / (2 * delta);
        }

        return differential;
    } 
} } } // namespace algo { namespace qn { namespace detail {
