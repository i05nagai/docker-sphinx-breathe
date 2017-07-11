#include "algo/qn/pre_compiled_header.h"
#include "algo/qn/IQuasiNewton.h"
#include "algo/ad/dual.hpp"

namespace algo { namespace qn {
    template <typename T>
    ublas::vector<double> IQuasiNewton<T>::operator()(
        const ublas::vector<double>& x0,
        const function_type& f,
        const std::shared_ptr<ILineSearcher> searcher)
    {
        return this->doOperatorParenthesis(x0, f, searcher);
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

    template
    ublas::vector<double> IQuasiNewton<double>::operator()(
        const ublas::vector<double>& x0,
        const double_function_type& f,
        const std::shared_ptr<ILineSearcher> searcher);
    template
    ublas::vector<double> IQuasiNewton<dual_type>::operator()(
        const ublas::vector<double>& x0,
        const dual_function_type& f,
        const std::shared_ptr<ILineSearcher> searcher);
} } // namespace algo { namespace qn {
