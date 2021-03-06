/*
 **************************************************************
 *         C++ Mathematical Expression Toolkit Library        *
 *                                                            *
 * Simple Example 4                                           *
 * Author: Arash Partow (1999-2013)                           *
 * URL: http://www.partow.net/programming/exprtk/index.html   *
 *                                                            *
 * Copyright notice:                                          *
 * Free use of the Mathematical Expression Toolkit Library is *
 * permitted under the guidelines and in accordance with the  *
 * most current version of the Common Public License.         *
 * http://www.opensource.org/licenses/cpl1.0.php              *
 *                                                            *
 **************************************************************
*/


#include <cstdio>
#include <string>
#include "exprtk.hpp"


template <typename T>
void fibonacci()
{
   typedef exprtk::symbol_table<T>      symbol_table_t;
   typedef exprtk::expression<T>          expression_t;
   typedef exprtk::parser<T>                  parser_t;
   typedef exprtk::function_compositor<T> compositor_t;

   compositor_t compositor;

   compositor
      .add("fibonacci_impl",
           "switch                        "
           "{                             "
           "  case x == 0 : 0;            "
           "  case x == 1 : 1;            "
           "  default     :               "
           "    while ((x := (x - 1)) > 0)"
           "    {                         "
           "      w := z;                 "
           "      z := z + y;             "
           "      y := w;                 "
           "      z                       "
           "    };                        "
           "}                             ",
           "x","y","z","w");

   compositor
      .add("fibonacci",
           "fibonacci_impl(x,0,1,0)",
           "x");

   T x = T(0);

   symbol_table_t& symbol_table = compositor.symbol_table();
   symbol_table.add_constants();
   symbol_table.add_variable("x",x);

   std::string expression_str = "fibonacci(x)";

   expression_t expression;
   expression.register_symbol_table(symbol_table);

   parser_t parser;

   parser.compile(expression_str,expression);

   for (std::size_t i = 0; i < 40; ++i)
   {
      x = i;
      T result = expression.value();
      printf("fibonacci(%3d) = %10.0f\n",
             static_cast<unsigned int>(i),
             result);
   }
}

int main()
{
   fibonacci<double>();
   return 0;
}
