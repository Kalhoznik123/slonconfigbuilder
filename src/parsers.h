#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/variant.hpp>




namespace parsers {

namespace internal_abonent_parser{

using mask_t = boost::variant<int,std::string>;

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
        (parsers::internal_abonent_parser::mask_t, mask)
        )




namespace parsers {

    namespace interface_parser {

    using namespace boost::spirit;

    template <typename Iterator>
    struct interface_parser : qi::grammar<Iterator, InterfaceParseRes(),ascii::space_type>
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

        qi::rule<Iterator, InterfaceParseRes(),ascii::space_type> start;
    };



    inline bool parse(const std::string& parsed_string,  InterfaceParseRes& parse_res){

        using iterator_type = std::string::const_iterator;
        interface_parser<iterator_type> parser;
        std::string::const_iterator iter = parsed_string.begin();
        std::string::const_iterator end = parsed_string.end();
        bool res = boost::spirit::qi::phrase_parse(iter,end,parser,boost::spirit::ascii::space,parse_res);

        return res;
    }

    }


    namespace internal_abonent_parser {

    using namespace boost::spirit;
    template <typename Iterator>
    struct internal_abonent_parser : qi::grammar<Iterator,IAbonentParseRes(),ascii::space_type>{
        internal_abonent_parser():internal_abonent_parser::base_type(start){

            doted_string %= +qi::digit >> qi::char_('.') >>+qi::digit >> qi::char_('.')>> +qi::digit >>qi::char_('.')>>+qi::digit;

            start %= doted_string >> *qi::lit(' ') >> (doted_string | qi::int_ );

        }

        qi::rule<Iterator,std::string()> doted_string;
        qi::rule<Iterator, IAbonentParseRes(),ascii::space_type> start;
    };


    inline bool parse(const std::string& parsed_string,  IAbonentParseRes& parse_res){

        using iterator_type = std::string::const_iterator ;
        internal_abonent_parser<iterator_type> parser;
        std::string::const_iterator iter = parsed_string.begin();
        std::string::const_iterator end = parsed_string.end();
        bool res = boost::spirit::qi::phrase_parse(iter,end,parser,boost::spirit::ascii::space,parse_res);

        return res;
    }


    }

}


