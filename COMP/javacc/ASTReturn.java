/* Generated By:JJTree: Do not edit this line. ASTReturn.java Version 6.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=false,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
import java.util.ArrayList;

public
class ASTReturn extends SimpleNode {
  public ASTReturn(int id) {
    super(id);
  }

  public ASTReturn(Jmm p, int id) {
    super(p, id);
  }

  @Override
  public void analyzeSemantics(ArrayList<SymbolTable> symbolTables, ArrayList<String> errors){

    for(int i = 0; i < this.jjtGetNumChildren(); i++){

      this.jjtGetChild(i).setMethod(this.getMethod());
      this.jjtGetChild(i).analyzeSemantics(symbolTables, errors);

    }

  }

  @Override
  public String getCode(ArrayList<SymbolTable> symbolTables, SimpleNode stackMethod){

    StringBuilder code = new StringBuilder("");

    SimpleNode first_child = (SimpleNode) this.jjtGetChild(0);

    int variable_index = 0;
    String variable_type = "";

    for(int i = 0; i < symbolTables.size(); i++){

      if(symbolTables.get(i).getName().equals(this.method) || symbolTables.get(i).getName().equals("global")){

        for(int j = 0; j < symbolTables.get(i).getArguments().size(); j++){
          if(symbolTables.get(i).getArguments().get(j).getName().equals(first_child.getVal())){
            variable_index = j + 1;
            variable_type = symbolTables.get(i).getArguments().get(j).getType();
          }
        }

        for(int j = 0; j < symbolTables.get(i).getVariables().size(); j++){

          if(symbolTables.get(i).getVariables().get(j).getName().equals(first_child.getVal())){

            if(this.method.equals("main")){
              variable_index = j + 1;
            }
            else{
              variable_index = symbolTables.get(i).getArguments().size() + j + 1;
            }
            variable_type = symbolTables.get(i).getVariables().get(j).getType();

          }

        }

      }

    }

    if(variable_type.equals("Int")){
      code.append("iload " + variable_index + "\n");
      stackMethod.incStack();
      stackMethod.updateMaxStack();
      code.append("ireturn\n");
    }
    else{
      // TO DO: add other types
      code.append("aload " + variable_index + "\n");
      stackMethod.incStack();
      stackMethod.updateMaxStack();
      code.append("return\n");
    }

    return code.toString();

  }

}
/* JavaCC - OriginalChecksum=7975c49ebbffce06e787d10236b530ff (do not edit this line) */