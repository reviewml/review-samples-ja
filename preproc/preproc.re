= preprocのためのサンプル

@<list>{hello.rb}は@<tt>{scripts/hello.rb}のソースを本文内に埋め込んでいます。

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

「@<tt>{#@mapfile(ファイル名)}」から「@<tt>{#@end}」は、ファイル名の中身を本文中に埋め込むために
使われる記法です。これは、@<tt>{review-preproc}コマンドを実行することで実現できます。

このプロジェクトのRakefileでは、このコマンドを実行するためのtaskが定義されています。
以下のように実行すれば、コマンドが実行されます。

//cmd{
rake preproc
//}

一部だけ抜粋することもできます。こちらは「@<tt>{#@maprange}」を使います。
抜粋したい部分は「@<tt>{#@range_begin}」と「@<tt>{#@range_end}」でくくります。

//list[range.rb][range.rb(抜粋)]{
#@maprange(scripts/range.rb,sample)
  def hello(name)
    print "hello, #{name}!\n"
  end
#@end
//}

もっとも、Ruby以外では「@<tt>{#@range_begin}」などがコメントと解釈されない
場合もあります。そのような場合、コメント内に「@<tt>{#@@range_begin}」と
「@<tt>{#@@range_end}」とを埋め込みます。 

//list[range.c][range.c(抜粋)]{
#@maprange(scripts/range.c,sample)
void
put_hello(char *name)
{
  printf("hello, %s!\n", name);
}
#@end
//}

このようにすると、Cなどの言語でもソースを埋め込むことができるようになります。