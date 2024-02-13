#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <variant>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>





namespace parsers {

namespace internal_abonent_parser{

using mask_t = std::variant<int,std::string>;

struct InternalAbonent_t{
    std::string ip_address;
    mask_t mask;
};

}

namespace interface_parser {

struct Interface_t{
    int speed;
    std::string mode;
};

}
}


BOOST_FUSION_ADAPT_STRUCT(
        parsers::interface_parser::Interface_t,
        (int, speed)
        (std::string, mode)
        )

BOOST_FUSION_ADAPT_STRUCT(
        parsers::internal_abonent_parser::InternalAbonent_t,
        (std::string, speed)
        (parsers::internal_abonent_parser::mask_t, mode)
        )




namespace parsers {

    namespace interface_parser {

    using namespace boost::spirit;

    template <typename Iterator>
    struct interface_parser : qi::grammar<Iterator, Interface_t(),ascii::space_type>
    {
        interface_parser() : interface_parser::base_type(start)
        {
            using qi::int_;
            using qi::lit;
            using qi::double_;
            using qi::lexeme;
            using ascii::char_;


            start %= int_ >> *qi::alpha;


        }

        qi::rule<Iterator, Interface_t(),ascii::space_type> start;
    };



    inline bool parse(const std::string& parsed_string,  Interface_t& parse_res){

        using iterator_type = std::string::const_iterator ;
        interface_parser<iterator_type> parser;
        std::string::const_iterator iter = parsed_string.begin();
        std::string::const_iterator end = parsed_string.end();
        bool res = boost::spirit::qi::phrase_parse(iter,end,parser,boost::spirit::ascii::space,parse_res);

        return res;
    }











    }

}


