/* Generated By:JJTree: Do not edit this line. ASTArgs.java Version 6.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=false,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
import java.util.ArrayList;

public
class ASTArgs extends SimpleNode {
  public ASTArgs(int id) {
    super(id);
  }

  public ASTArgs(Jmm p, int id) {
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

    for(int j = 0; j < this.jjtGetNumChildren(); j++){
      
      if(this.jjtGetChild(j).toString().equals("Identifier")){
        
        SimpleNode arg = (SimpleNode) this.jjtGetChild(j);

        // ======================== Gets type of caller ========================

        int variable_index = 0;
        String variable_type = "";

        for(int i = 0; i < symbolTables.size(); i++){

          if(symbolTables.get(i).getName().equals(this.method) || symbolTables.get(i).getName().equals("global")){

            for(int k = 0; k < symbolTables.get(i).getVariables().size(); k++){

              if(symbolTables.get(i).getVariables().get(k).getName().equals(arg.getVal())){

                variable_index = k + 1;
                variable_type = symbolTables.get(i).getVariables().get(k).getType();

              }

            }

          }

        }

        if(variable_type.equals("Int")){
          code.append("iload " + variable_index + "\n");
          stackMethod.incStack();
          stackMethod.updateMaxStack();
        }
        else{
          // TO DO: add other types
          code.append("aload " + variable_index + "\n");
          stackMethod.incStack();
          stackMethod.updateMaxStack();
        }

        // ====================================================================


      }
      else if(this.jjtGetChild(j).toString().equals("Value")){
        if(this.jjtGetChild(j).getVal().equals("true")){
          code.append("bipush 1\n");
        }
        else if(this.jjtGetChild(j).getVal().equals("false")){
          code.append("bipush 0\n");
        }
        else{
          code.append("bipush " + this.jjtGetChild(j).getVal() + "\n");
        }
        
        stackMethod.incStack();
        stackMethod.updateMaxStack();
      }
      else if(this.jjtGetChild(j).toString().equals("ArrayAccess")){
        code.append(this.jjtGetChild(j).getCode(symbolTables, stackMethod));
      }

    }

    return code.toString();

  }

}
/* JavaCC - OriginalChecksum=710441fe0986107d1fcbe92c85727d55 (do not edit this line) */
