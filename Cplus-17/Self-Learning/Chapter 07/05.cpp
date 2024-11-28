#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <vector>
#include <sstream> // string stream

int main()
{
    // 1. 字符串转换为数字
    // std::stoi(std::string)    string to int
    // 相对于的 对应的有 std::to_string(type_name) 把其他类型转换为string类型
    std::string text{"124678"};
    int number{std::stoi(text)};
    // 还可以转换为其他类型
    // stol(), stoll(), stoul(),stoull()
    // stof(), stod(), stold()
    // 上面分别是 long, long long, unsigned long, unsigned long long
    //           float, double, long double

    // 2. 字符串流 std::stringstream
    // 它部将字符直接输出到计算机屏幕，而是将字符收集到 string 对象
    // 然后可以在任意时刻获取这个 string 对象
    // 用法同 std::cout
    {
        std::vector<double> values;
        std::cout << "输入数字数量 n: ";
        size_t num{};
        std::cin >> num;
        for (size_t i{}; i < num; ++i)
        {
            double d{};
            std::cin >> d;
            values.push_back(d);
        }

        std::stringstream ss;
        for (size_t i{}; i < num; ++i)
        {
            // ! 这里没有 std::cout
            // ! 这里是存储，还没有打印
            ss << std::setprecision(4) << std::setw(7) << std::right << values[i];
            if ((i + 1) % 5 == 0)
                ss << std::endl;
        }
        // ! std::stringstream.str() 函数 可以得到一个 std::string 对象
        // 它包含到目前为止，流中收集的所有字符
        std::string s{ss.str()};
        std::cout << s << std::endl;
    }

    // 3. 国际字符串
    // std::wstring     wchar_t 类型
    // 它是宽字符（wide character）字符串类型，用来表示比单字节字符更多的字符集（例如多语言文本）。
    // wchar_t 的宽度和编码方式取决于具体平台。
    // 在 Windows 上，wchar_t 通常是 16 位，对应于 UTF-16 编码。
    // 在 Unix/Linux 上，wchar_t 通常是 32 位，对应于 UTF-32 编码

    // std::u16string   char16_t 类型
    // char16_t 是固定 16 位的类型，专门为 Unicode 的 UTF-16 编码设计

    // std::u32string   char32_t 类型
    // char32_t 是固定 32 位的类型，每个元素直接表示一个 Unicode 码点，无需代理对

    // 1. Unicode: 一个字符编码标准，旨在为所有字符分配唯一的数字标识符（码点），
    //    解决不同平台、语言和应用程序之间的字符编码不一致问题。
    //    每个字符有一个唯一的 Unicode 码点，使用 U+XXXX 格式表示，如 U+0041 表示字符 "A"。

    // 2. UTF-8: 可变长度编码，使用 1 至 4 字节表示字符。
    //    - 兼容 ASCII，常见字符（如拉丁字母）使用 1 字节表示。
    //    - 较少使用的字符（如汉字）使用 3 或 4 字节。
    //    - 适合大多数 Web 应用，节省空间，广泛使用。
    //    示例：
    //      'A' -> U+0041 -> 0x41 (1 字节)
    //      '你' -> U+4F60 -> 0xE4 0xBD 0xA0 (3 字节)
    //      '😊' -> U+1F60A -> 0xF0 0x9F 0x98 0x8A (4 字节)

    // 3. UTF-16: 可变长度编码，使用 2 字节表示常见字符，使用代理对（2x16位）表示较少使用字符。
    //    - 对于基本字符集（如拉丁字母、汉字等）使用 2 字节。
    //    - 对于码点超过 U+FFFF 的字符，使用代理对表示。
    //    - 适用于 Java、Windows 和一些 Web 应用。
    //    示例：
    //      'A' -> U+0041 -> 0x0041 (2 字节)
    //      '你' -> U+4F60 -> 0x4F60 (2 字节)
    //      '😊' -> U+1F60A -> 0xD83D 0xDE0A (代理对, 4 字节)

    // 4. UTF-32: 固定长度编码，每个字符使用 4 字节表示。
    //    - 每个字符占用固定的 4 字节，不需要代理对。
    //    - 内存占用较大，但对处理字符直接且简单。
    //    - 适用于对字符大小有严格要求的场景。
    //    示例：
    //      'A' -> U+0041 -> 0x00000041 (4 字节)
    //      '你' -> U+4F60 -> 0x00004F60 (4 字节)
    //      '😊' -> U+1F60A -> 0x0001F60A (4 字节)

    // 选择编码方式时，考虑存储效率、内存占用及应用场景的需求。
    //    - **UTF-8**：广泛使用，节省存储空间。
    //    - **UTF-16**：多语言支持，常用于 Java 和 Windows。
    //    - **UTF-32**：适合对字符大小固定有要求的场景。

    std::wstring wstring1{L"Manba out."}; // ! 要加 'L' 字符， 指定字面量为 wchar_t 类型的字符组成
    std::wcout << wstring1 << std::endl;    // ! 输出要用 wcout 宽字符输出
    // ! 前面的函数加上 'w' 便可对 wstring 对象使用

    std::u16string u16sting1{u"I'm u16sting1."}; // ! 同上，要加 'u' 字符

    std::u32string u32sting1{U"I'm u32sting1."}; // ! 加 'U' 字符，注意是大写


    // 4. 原始字符串字面量
    // 针对包含特殊字符的字面量，如正则表达式，需要包含 \ 等特殊字符
    // 在字符串字面量前加上 R 前缀，然后包裹在圆括号里面，便不需要转义字符来表示特殊字符
    // ! R"(string)"
    auto originString1{R"(Manbd "out", haha\\ ,dawga..\.wad)"};
    // ! 注意，字符串字面量里面不能出现 ")，会编译错误
    // auto wrongString{R"(wrong string:" ") ")}; // 编译器会拒绝编译
    // 可以使用任意的字符标定 原始字符串字面量的界限，如 '*' "la-lala"，称之为 char_sequence
    // ! 注意 char_sequence 不能超过16个字符，不能包括 圆括号，空格，控制字符和反斜杠字符
    auto originString2{R"*(hahahahah*)\\//)*"};
    auto originString3{R"la-lala(hahahahah*)\\//)la-lala"};
    std::cout << originString1 << std::endl;
    std::cout << originString2 << std::endl;
    std::cout << originString3 << std::endl;

    
    return 0;
}
