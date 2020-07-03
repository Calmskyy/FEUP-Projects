/* Generated By:JJTree: Do not edit this line. ASTNewClass.java Version 4.3 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=false,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
import java.util.ArrayList;
public
class ASTNewClass extends SimpleNode {
  public ASTNewClass(int id) {
    super(id);
  }

  public ASTNewClass(Jmm p, int id) {
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

    code.append("new " + this.jjtGetChild(0).getVal() + "\n");
    code.append("dup\n");
    code.append("invokespecial " + this.jjtGetChild(0).getVal() + "/<init>()V\n");
    //stackMethod.incStack(); 

    return code.toString();

  }
}
/* JavaCC - OriginalChecksum=111e72dc2948b7d0af7458a03d9d4684 (do not edit this line) */