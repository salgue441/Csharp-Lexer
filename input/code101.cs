using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

// ESTO ES UN COMENTARIO

/* comentario multilinea
    Otra for mas
    La ultima ****
*/

class Program
{
    static void Main(string[] args)
    {
        1234567890;
        1_2_34;
        _12_34;
        1 2 3 4;
        1_2_3_4lU;
        123l;
        123Lu;
        123u;
        123Ul;
        123.456;

        0x1234567890AbcDEf;
        0x1_2_34;
        0x_12_34;

        0xFFu;
        0xFFUl;
        0xFFl;
        0xFFLu;

        0b1010101010101010101010101010101010101010101010101010101010101010;
        0;
        0b;
        0b_;
        0b_1;
        0b1_;
        0b1_0;
        0;
        0B;
        0B_;

        1.1;
        2.2;
        3.3;
        1.234_567;      // double
        .3e5f;          // float
        2_345E-2_0;     // double
        15D;            // double
        19.73M;         // decimal
        1.F;            // parsed as a member access of F due to non-digit after .
        1_.2F;          // invalid; no trailing _ allowed in integer part
        1._234;         // parsed as a member access of _234 due to non-digit after .
        1.234_;         // invalid; no trailing _ allowed in fraction
        .3e_5F;         // invalid; no leading _ allowed in exponent
        .3e5_F;         // invalid; no trailing _ allowed in exponent

        // deberia resaltarse
        'a';
        '\n';
        '\t';
        '\b';
        '\r';
        '\f';
        '\v';
        '\0';
        '\a';
        '\x0';
        '\x01';
        '\x012';
        '\xaFbD';
        '\u1234';
        '\U12345678';

        // No deberia resaltarse
        '\';
        ''';
        ''';
        ''';
        '\x01Bg';
        '\x012345';
        '\u1234ee';
        '\u123';

        string a = "Happy birthday, Joel"; // Happy birthday, Joel
        string b = @"Happy birthday, Joel"; // Happy birthday, Joel
        string c = "hello \t world"; // hello world
        string d = @"hello \t world"; // hello \t world
        string e = "Joe said \"Hello\" to me"; // Joe said "Hello" to me
        string f = @"Joe said ""Hello"" to me"; // Joe said "Hello" to me
        string g = "\\\\server\\share\\file.txt"; // \\server\share\file.txt
        string h = @"\\server\share\file.txt"; // \\server\share\file.txt
        string i = "one\r\ntwo\r\nthree";
        string j = @"one
        two
        three";

        Console.WriteLine("Hello World!!");
    }
}
