#include "ExplicitLineSearcher.h"

namespace algo { namespace qn {
    ExplicitLineSearcher::ExplicitLineSearcher(const functor_type& f)
    : _f(f)
    {
    }

    //min f(x + ap)
    ublas::vector<double> ExplicitLineSearcher::doOperatorParenthesis(
        const ublas::vector<double>& p,
        const ublas::vector<double>& x)
    {
        return _f(p, x);
    }

} } // namespace algo { namespace qn {
