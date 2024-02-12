#pragma once
#include <iostream>
#include <string>
#include <boost/spirit/include/qi.hpp>
#include <functional>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>





namespace parsers {

namespace interface_parser {

struct result{
    int speed;
    std::string mode;
};

}
}


BOOST_FUSION_ADAPT_STRUCT(
        parsers::interface_parser::result,
        (int, speed)
        (std::string, mode)
        )


namespace parsers {

    namespace interface_parser {

    using namespace boost::spirit;

    template <typename Iterator>
    struct interface_parser : qi::grammar<Iterator, result(),ascii::space_type>
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

        qi::rule<Iterator, result(),ascii::space_type> start;
    };



    inline bool parse(const std::string& parsed_string,  result& parse_res){

        using iterator_type = std::string::const_iterator ;
        interface_parser<iterator_type> parser;
        std::string::const_iterator iter = parsed_string.begin();
        std::string::const_iterator end = parsed_string.end();
        bool res = boost::spirit::qi::phrase_parse(iter,end,parser,boost::spirit::ascii::space,parse_res);

        return res;
    }











    }

}


