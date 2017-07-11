#include "ILineSearcher.h"

namespace algo { namespace qn {
    namespace ublas = boost::numeric::ublas;

    ublas::vector<double> ILineSearcher::operator()(
        const ublas::vector<double>& p,
        const ublas::vector<double>& x)
    {
        return this->doOperatorParenthesis(p, x);
    }
} } // namespace algo { namespace qn {
