#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <cstdint>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/variant.hpp>




namespace parsers {

using mask_t = boost::variant<int,std::string>;

namespace internal_abonent_parser{


struct IAbonentParseRes{
    std::string ip_address;
    mask_t mask;
};

}

namespace interface_parser {

struct InterfaceParseRes{
    int speed;
    std::string mode;
};

}

namespace remote_abonent_parser{

struct RAbonentParseRes{
    int devicenumber;
    std::string ip_address;
    mask_t mask;
};
}
}


BOOST_FUSION_ADAPT_STRUCT(
        parsers::interface_parser::InterfaceParseRes,
        (int, speed)
        (std::string, mode)
        )

BOOST_FUSION_ADAPT_STRUCT(
        parsers::internal_abonent_parser::IAbonentParseRes,
        (std::string, ip_address)
        (parsers::mask_t, mask)
        )

BOOST_FUSION_ADAPT_STRUCT(
        parsers::remote_abonent_parser::RAbonentParseRes,
        (int, devicenumber),
        (std::string, ip_address),
        (parsers::mask_t,mask)
        )


namespace parsers {
    using namespace boost::spirit;

    template <typename Parser,typename ParseResult>
    bool Parse(const std::string& parsed_string,  ParseResult& parse_res){
        Parser parser;
        std::string::const_iterator iter = parsed_string.begin();
        std::string::const_iterator end = parsed_string.end();
        bool res = boost::spirit::qi::phrase_parse(iter,end,parser,boost::spirit::ascii::space,parse_res);

        return res;
    }



    namespace interface_parser {

    using namespace boost::spirit;

    template <typename Iterator>
    struct interface_parser : qi::grammar<Iterator, InterfaceParseRes(),ascii::space_type>
    {
        interface_parser() : interface_parser::base_type(start){
            using qi::int_;

            start %= unsigned_parser >> repeat(2)[qi::char_("DFH")];
        }
        qi::uint_parser<std::uint8_t,10,1,3> unsigned_parser;
        qi::rule<Iterator, InterfaceParseRes(),ascii::space_type> start;
    };
    }


    namespace internal_abonent_parser {

    using namespace boost::spirit;
    template <typename Iterator>
    struct internal_abonent_parser : qi::grammar<Iterator,IAbonentParseRes(),ascii::space_type>{
        internal_abonent_parser():internal_abonent_parser::base_type(start){

            doted_string %= qi::repeat(1,3)[qi::digit] >>
                            qi::char_('.') >>qi::repeat(1,3)[qi::digit] >>
                            qi::char_('.')>> qi::repeat(1,3)[qi::digit] >>
                            qi::char_('.')>>qi::repeat(1,3)[qi::digit];

            start %= doted_string >> *qi::lit(' ') >> (doted_string | qi::int_ );
        }

        qi::rule<Iterator,std::string()> doted_string;
        qi::rule<Iterator, IAbonentParseRes(),ascii::space_type> start;
    };
    }

    namespace remote_abonent_parser {


    using namespace boost::spirit;
    template <typename Iterator>
    struct remote_abonent_parser : qi::grammar<Iterator,RAbonentParseRes(),ascii::space_type>{
        remote_abonent_parser(): remote_abonent_parser::base_type(start){
            doted_string %= qi::repeat(1,3)[qi::digit] >>
                            qi::char_('.') >>qi::repeat(1,3)[qi::digit] >>
                            qi::char_('.')>> qi::repeat(1,3)[qi::digit] >>
                            qi::char_('.')>>qi::repeat(1,3)[qi::digit];

            start %= qi::int_ >> doted_string >> *qi::lit(' ') >> (doted_string | qi::int_ );
        }

        qi::rule<Iterator,std::string()> doted_string;
        qi::rule<Iterator,RAbonentParseRes(),ascii::space_type> start;
    };

    }
}
