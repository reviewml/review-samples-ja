= preprocのためのサンプル

@<list>{hello.rb}は@<tt>{scripts/hello.rb}のソースを本文内に埋め込んでいます。

//list[hello.rb][hello.rb]{
 //list[hello.rb][hello.rb]{
 #@mapfile(scripts/hello.rb)
 #!/usr/bin/env ruby
 
 class Hello
   def hello(name)
     print "hello, #{name}!\n"
   end
 end
 
 if __FILE__ == $0
   Hello.new.hello("world")
 end
 #@end
 //}
//}

「@<tt>{#@mapfile(ファイル名)}」から「@<tt>{#@end}」は、指定したファイル名のファイル全体を本文中に埋め込むための記法です。
埋め込む際には、@<tt>{review-preproc}コマンドを実行します。

まず、@<list>{hello.rb.1}のように、引用したい部分に「@<tt>{#@mapfile()}」と「@<tt>{#@end}」だけを書きます。
ここでは@<tt>{//list}ブロック内にこの２行だけを記述しています。


//list[hello.rb.1][hello.re]{
 //list[hello.rb.1][hello.re]{
 #@mapfile(scripts/hello.rb)
 #@end
 //}
//}

このソースに対して、@<tt>{review-preproc}コマンドを実行します。すると、変換結果の*.reファイルを標準出力に出力します。

//cmd{
$ review-preproc hello.re
//}

@<tt>{--replace}オプションをつければ、ファイルそのものを置き換えるようになります。

//cmd{
$ review-preproc --replace hello.re
//}

なお、このプロジェクトのRakefileでは、このコマンドを実行するためのtaskが定義されています。
以下のように実行すれば、コマンドが実行されます。

//cmd{
$ rake preproc
//}

対象ファイルの一部だけ抜粋することもできます。こちらは「@<tt>{#@maprange}」という記法を使います。

対象ファイルの抜粋したい部分の前後に、「@<tt>{#@range_begin(ID)}」と「@<tt>{#@range_end}」という記法を埋め込んでおきます。
@<tt>{#@range_begin}の引数には、その断片を抽出する際に使用するIDを指定します。@<list>{range.rb}の例では「sample」というIDにしています。

//list[range.rb][range.rb(全体)]{
 #!/usr/bin/env ruby
 
 class Hello
 #@range_begin(sample)
   def hello(name)
     print "hello, #{name}!\n"
   end
 #@range_end(sample)
 end
 
 if __FILE__ == $0
   Hello.new.hello("world")
 end
//}

*.reファイルの方には、「@<tt>{#@mapfile(ファイル名)}」ではなく「@<tt>{#@maprange(ファイル名,ID)}」を記述します。

//list[range.rb.1][range.rb(抜粋前)]{
 //list[range.rb][range.rb(抜粋)]{
 #@maprange(scripts/range.rb,sample)
 #@end
 //}
//}

あとは、先ほど同様、@<tt>{review-preproc}コマンドか@<tt>{rake preproc}コマンドを実行します。
そうすると、scripts/range.rbの一部が抽出されて埋め込まれます。

//list[range.rb.2][range.rb(抜粋後)]{
 //list[range.rb][range.rb(抜粋)]{
 #@maprange(scripts/range.rb,sample)
   def hello(name)
     print "hello, #{name}!\n"
   end
 #@end
 //}
//}

もっとも、Ruby以外では「@<tt>{#@range_begin}」などがコメントと解釈されないこともあります。
そのような場合、その言語のコメントの中に「@<tt>{#@@range_begin}」と「@<tt>{#@@range_end}」とを記述します。

Cのソースを例にします。対象となるrange.cは@<list>{range.c}のようになります。

//list[range.c][range.c(全体)]{
#include <stdio.h>

/* #@@range_begin(sample)  */
void
put_hello(char *name)
{
  printf("hello, %s!\n", name);
}
/* #@@range_end(sample) */

int main()
{
  put_hello("world");
}
//}

put_hello関数の定義の前後で「@<tt>{#@@range_begin}」と「@<tt>{#@@range_end}」が使われています。

これに対し、*.reファイルでは@<tt>{#@maprange(scripts/range.c,sample)}と@<tt>{#@end}を記述します。

//list[range.c.1][range.c(抜粋)]{
 //list[range.c][range.c(抜粋)]{
 #@maprange(scripts/range.c,sample)
 #@end
 //}
//}

結果、@<list>{range.c.2}のようになります。

//list[range.c.2][range.c(抜粋)]{
 //list[range.c][range.c(抜粋)]{
 #@maprange(scripts/range.c,sample)
 void
 put_hello(char *name)
 {
   printf("hello, %s!\n", name);
 }
 #@end
 //}
//}

このようにすると、Cなどの言語のファイルに対しても、ソースの一部を抽出して埋め込むことができます。
