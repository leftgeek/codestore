CodeStore是一个集成了代码的编辑,分类管理以及用户代码共享的软件  
采用QT C++编写,用Qt Creator可打开项目  
但是不同用户代码的共享不是通过网络实现,而是通过本地数据库来实现的  

`Project file tree:`

├── category.xml  
├── CodeStore.pro  
├── CodeStore.pro.user  
├── CodeStore.pro.user.2.3pre1  
├── CodeStore.pro.user.2.5pre1  
├── config  
│   ├── help.html  
│   ├── syntax  
│   │   ├── abap.xml  
│   │   ├── abc.xml  
│   │   ├── actionscript.xml  
│   │   ├── ada.xml  
│   │   ├── ahdl.xml  
│   │   ├── alert_indent.xml  
│   │   ├── alert.xml  
│   │   ├── ample.xml  
│   │   ├── ansic89.xml  
│   │   ├── ansys.xml  
│   │   ├── apache.xml  
│   │   ├── asm6502.xml  
│   │   ├── asm-avr.xml  
│   │   ├── asm-dsp56k.xml  
│   │   ├── asm-m68k.xml  
│   │   ├── asn1.xml  
│   │   ├── asp.xml  
│   │   ├── asterisk.xml  
│   │   ├── awk.xml  
│   │   ├── bash.xml  
│   │   ├── bibtex.xml  
│   │   ├── bmethod.xml  
│   │   ├── boo.xml  
│   │   ├── cgis.xml  
│   │   ├── cg.xml  
│   │   ├── changelog.xml  
│   │   ├── cisco.xml  
│   │   ├── clipper.xml  
│   │   ├── cmake.xml  
│   │   ├── coffee.xml  
│   │   ├── coldfusion.xml  
│   │   ├── commonlisp.xml  
│   │   ├── component-pascal.xml  
│   │   ├── cpp.xml  
│   │   ├── css-php.xml  
│   │   ├── css.xml  
│   │   ├── cs.xml  
│   │   ├── cue.xml  
│   │   ├── c.xml  
│   │   ├── debianchangelog.xml  
│   │   ├── debiancontrol.xml  
│   │   ├── desktop.xml  
│   │   ├── diff.xml  
│   │   ├── djangotemplate.xml  
│   │   ├── doxygenlua.xml  
│   │   ├── doxygen.xml  
│   │   ├── dtd.xml  
│   │   ├── d.xml  
│   │   ├── eiffel.xml  
│   │   ├── email.xml  
│   │   ├── erlang.xml  
│   │   ├── euphoria.xml  
│   │   ├── e.xml  
│   │   ├── ferite.xml  
│   │   ├── fgl-4gl.xml  
│   │   ├── fgl-per.xml  
│   │   ├── fortran.xml  
│   │   ├── freebasic.xml  
│   │   ├── fsharp.xml  
│   │   ├── fstab.xml  
│   │   ├── gap.xml  
│   │   ├── gdb.xml  
│   │   ├── gdl.xml  
│   │   ├── gettext.xml  
│   │   ├── glsl.xml  
│   │   ├── gnuassembler.xml  
│   │   ├── go.xml  
│   │   ├── grammar.xml  
│   │   ├── haskell.xml  
│   │   ├── haxe.xml  
│   │   ├── html-php.xml  
│   │   ├── html.xml  
│   │   ├── idconsole.xml  
│   │   ├── idl.xml  
│   │   ├── ilerpg.xml  
│   │   ├── inform.xml  
│   │   ├── ini.xml  
│   │   ├── javadoc.xml  
│   │   ├── javascript-php.xml  
│   │   ├── javascript.xml  
│   │   ├── java.xml  
│   │   ├── json.xml  
│   │   ├── jsp.xml  
│   │   ├── katetemplate.xml  
│   │   ├── kbasic.xml  
│   │   ├── language.dtd  
│   │   ├── latex.xml  
│   │   ├── ldif.xml  
│   │   ├── lex.xml  
│   │   ├── lilypond.xml  
│   │   ├── literate-haskell.xml  
│   │   ├── logtalk.xml  
│   │   ├── lpc.xml  
│   │   ├── lsl.xml  
│   │   ├── lua.xml  
│   │   ├── m3u.xml  
│   │   ├── mab.xml  
│   │   ├── makefile.xml  
│   │   ├── mandoc.xml  
│   │   ├── mason.xml  
│   │   ├── matlab.xml  
│   │   ├── maxima.xml  
│   │   ├── mediawiki.xml  
│   │   ├── mergetagtext.xml  
│   │   ├── metafont.xml  
│   │   ├── mips.xml  
│   │   ├── modelica.xml  
│   │   ├── modula-2.xml  
│   │   ├── monobasic.xml  
│   │   ├── mup.xml  
│   │   ├── nasm.xml  
│   │   ├── nemerle.xml  
│   │   ├── noweb.xml  
│   │   ├── objectivecpp.xml  
│   │   ├── objectivec.xml  
│   │   ├── ocaml.xml  
│   │   ├── octave.xml  
│   │   ├── oors.xml  
│   │   ├── opal.xml  
│   │   ├── pango.xml  
│   │   ├── pascal.xml  
│   │   ├── perl.xml  
│   │   ├── pgn.xml  
│   │   ├── php.xml  
│   │   ├── picsrc.xml  
│   │   ├── pike.xml  
│   │   ├── plasma-desktop-js.xml  
│   │   ├── postscript.xml  
│   │   ├── povray.xml  
│   │   ├── progress.xml  
│   │   ├── prolog.xml  
│   │   ├── purebasic.xml  
│   │   ├── python.xml  
│   │   ├── qml.xml  
│   │   ├── rapidq.xml  
│   │   ├── rexx.xml  
│   │   ├── rhtml.xml  
│   │   ├── rib.xml  
│   │   ├── roff.xml  
│   │   ├── rpmspec.xml  
│   │   ├── rsiidl.xml  
│   │   ├── ruby.xml  
│   │   ├── r.xml  
│   │   ├── sather.xml  
│   │   ├── scala.xml  
│   │   ├── scheme.xml  
│   │   ├── sci.xml  
│   │   ├── sed.xml  
│   │   ├── sgml.xml  
│   │   ├── sieve.xml  
│   │   ├── sisu.xml  
│   │   ├── sml.xml  
│   │   ├── spice.xml  
│   │   ├── sql-mysql.xml  
│   │   ├── sql-postgresql.xml  
│   │   ├── sql.xml  
│   │   ├── stata.xml  
│   │   ├── syntax.template  
│   │   ├── systemc.xml  
│   │   ├── tcl.xml  
│   │   ├── texinfo.xml  
│   │   ├── tibasic.xml  
│   │   ├── txt2tags.xml  
│   │   ├── uscript.xml  
│   │   ├── velocity.xml  
│   │   ├── verilog.xml  
│   │   ├── vhdl.xml  
│   │   ├── vrml.xml  
│   │   ├── winehq.xml  
│   │   ├── wml.xml  
│   │   ├── xharbour.xml  
│   │   ├── xmldebug.xml  
│   │   ├── xml.xml  
│   │   ├── xorg.xml  
│   │   ├── xslt.xml  
│   │   ├── xul.xml  
│   │   ├── yacas.xml  
│   │   ├── yacc.xml  
│   │   ├── yaml.xml  
│   │   └── zonnon.xml  
│   └── ui.xml  
├── headers  
│   ├── category.h  
│   ├── categoryPropertyWidget.h  
│   ├── code.h  
│   ├── codePropertyWidget.h  
│   ├── codeTree.h  
│   ├── codeTreeWidget.h  
│   ├── database.h  
│   ├── developWidget.h  
│   ├── findPasswordWidget.h  
│   ├── helpWidget.h  
│   ├── highlighter.h  
│   ├── importFileWidget.h  
│   ├── loginWidget.h  
│   ├── logTree.h  
│   ├── mainWindow.h  
│   ├── modifyPasswordWidget.h  
│   ├── newCategoryWidget.h  
│   ├── newFileWidget.h  
│   ├── newsWidget.h  
│   ├── personalCenterWidget.h  
│   ├── propertyWidget.h  
│   ├── recentFile.h  
│   ├── registerWidget.h  
│   ├── replaceWidget.h  
│   ├── searchWidget.h  
│   ├── sendEmail.h  
│   ├── startPageWidget.h  
│   ├── sync.h  
│   ├── tabWidget.h  
│   ├── textEditor.h  
│   └── user.h  
├── log.xml  
├── resource.qrc  
├── resources  
│   ├── help.html  
│   └── icons  
│       ├── edit-copy.png  
│       ├── edit-cut.png  
│       ├── edit-paste.png  
│       ├── edit-redo.png  
│       ├── edit-undo.png  
│       ├── file-new.png  
│       ├── file-open.png  
│       ├── file-quit.png  
│       ├── file-save-as.png  
│       ├── file-save.png  
│       ├── folder.png  
│       ├── page-develop.png  
│       ├── page-news.png  
│       ├── page-personalcenter.png  
│       ├── text-c.png  
│       ├── text-cpp.png  
│       ├── text-csharp.png  
│       ├── text-html.png  
│       ├── text-java.png  
│       └── text-plain.png  
└── sources  
    ├── codeTree.cpp  
    ├── control  
    │   ├── categoryControl.cpp  
    │   ├── codeControl.cpp  
    │   └── userControl.cpp  
    ├── database.cpp  
    ├── highlighter.cpp  
    ├── logTree.cpp  
    ├── main.cpp  
    ├── mainWindow.cpp  
    ├── model  
    │   ├── categoryModel.cpp  
    │   ├── codeModel.cpp  
    │   └── userModel.cpp  
    ├── recentFile.cpp  
    ├── sendEmail.cpp  
    ├── sync.cpp  
    └── widgets  
        ├── categoryPropertyWidget.cpp  
        ├── codePropertyWidget.cpp  
        ├── codeTreeWidget.cpp  
        ├── developWidget.cpp  
        ├── findPasswordWidget.cpp  
        ├── helpWidget.cpp  
        ├── importFileWidget.cpp  
        ├── loginWidget.cpp  
        ├── modifyPasswordWidget.cpp  
        ├── newCategoryWidget.cpp  
        ├── newFileWidget.cpp  
        ├── newsWidget.cpp  
        ├── personalCenterWidget.cpp  
        ├── propertyWidget.cpp  
        ├── registerWidget.cpp  
        ├── replaceWidget.cpp  
        ├── searchWidget.cpp  
        ├── startPageWidget.cpp  
        ├── tabWidget.cpp  
        └── textEditor.cpp  
`end`
