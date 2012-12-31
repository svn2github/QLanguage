/********************************************************************
	created:	2012/12/07
	created:	7:12:2012   22:54
	filename: 	\QCore\Library\combinator\alt.h
	file path:	\QCore\Library\combinator
	file base:	alt
	file ext:	h
	author:		lwch
	
	purpose:	
*********************************************************************/
#ifndef _QLANGUAGE_LIBRARY_COMBINATOR_ALT_H_
#define _QLANGUAGE_LIBRARY_COMBINATOR_ALT_H_

#include "combinator.h"

NAMESPACE_QLANGUAGE_LIBRARY_START
    template <typename I, typename O, typename IOO, typename E>
    class CombinatorAlt : public Combinator<I, O, IOO, E>
    {
        typedef Combinator<I, O, IOO, E> combinator_type;
    public:
        CombinatorAlt(combinator_type* first, combinator_type* second) : first(first), second(second) {}
        virtual ~CombinatorAlt() {}

        virtual bool parse(const I& input, O& output);

        virtual inline void destruct() { QLanguage::Library::destruct(this, has_destruct(*this)); }
        virtual inline const typename Combinator<I, O, IOO, E>::size_type objSize()const { return sizeof(*this); }
    protected:
        combinator_type* first;
        combinator_type* second;
    };
NAMESPACE_QLANGUAGE_LIBRARY_END

#endif