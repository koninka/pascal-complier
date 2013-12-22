#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include "parser.h"
#include "scanner.h"
#include "printer.h"

using namespace std;

int main(int argc, char *argv[])
{
	bool isErr = false;
	string errMsg;
   try {
		Printer printer;
		//Scanner scanner("test.tree");
		//SimpleParser parser(scanner);
		//printer.printParseTree(parser);
		//printer.printLexicalTable(scanner, true);
		//Scanner scanner1("test.tree");
		//Parser parser(scanner1);
		//parser.isDeclarationParse = false;
		//parser.ParseProgram();
  //    freopen("tree.asm", "w", stdout);
  //    parser.Generate();
		//cout << "-----------TABLE-----------" << endl << endl;
		//parser.PrintSymTable();
      //cout << endl << endl << "-----------ASM-----------" << endl << endl;
      //parser.Generate();
      //cout << "-----------BLOCK-----------" << endl << endl;
      //parser.PrintBlock();
		//parser.Parse();
		//printer.printLexicalTable(scanner1, true);
		//printer.printParseTree(parser);
      if (argc > 1) {
         if (argv[1][0] == '-') {
            for (int i = 1, len = strlen(argv[1]); i < len; i++) {
					for (int j = 2; j < argc; j++) {
						Scanner scanner(argv[j]);
						switch (argv[1][i]) {
							case 'T':
								printer.printLexicalTable(scanner, true);
								break;
							case 't':
								printer.printLexicalTable(scanner, false);
								break;
							case 'l':
								printer.printTestToFile(scanner, false);
								break;
							case 'L':
								printer.printTestToFile(scanner, true);
								break;
							case 'd':
								{
									Parser parser(scanner);
									printer.printDeclarationTable(parser, true);
								}
								break;
							case 'p':
								{
									Parser parser(scanner);
									printer.printProgramParseTree(parser);
								}
								break;
                     case 'g':
                        {
                           Parser parser(scanner);
                           printer.printAsmCode(parser);
                        }
                        break;
						}
					}
				}
         } else {
            Scanner scanner(argv[1]);
            printer.printTestToFile(scanner, false);
         }
      }
   } catch (CompilerException& e) {
		isErr = true;
		errMsg = e.getMessage();
   } catch (SimpleException& e) {
		isErr = true;
		errMsg = e.getMessage();
	} catch (SyntaxException& e) {
		isErr = true;
		errMsg = e.getMessage();
	} catch (DuplicateException& e) {
		isErr = true;
		errMsg = e.getMessage();
	} catch (OperatorException& e) {
		isErr = true;
		errMsg = e.getMessage();
	} catch (IdentifierNotFoundException& e) {
		isErr = true;
		errMsg = e.getMessage();
	} catch (IllegalExprException& e) {
		isErr = true;
		errMsg = e.getMessage();
	} catch (IncompatibleTypesException& e) {
		isErr = true;
		errMsg = e.getMessage();
	} catch (TypeDefinitionException& e) {
		isErr = true;
		errMsg = e.getMessage();
	} catch (WrongParametersException& e) {
		isErr = true;
		errMsg = e.getMessage();
	} catch (IncompatibleTypeArgException& e) {
		isErr = true;
		errMsg = e.getMessage();
	} catch (JumpNotAllowedException& e) {
		isErr = true;
		errMsg = e.getMessage();
	}
	if (isErr) {
		cout << errMsg << endl;
	}
	return 0;
}