/* Generated By:JJTree: Do not edit this line. ASTBoolean.java Version 6.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=false,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
import java.util.ArrayList;

public
class ASTBoolean extends SimpleNode {
  public ASTBoolean(int id) {
    super(id);
  }

  public ASTBoolean(Jmm p, int id) {
    super(p, id);
  }

  @Override
  public void analyzeSemantics(ArrayList<SymbolTable> symbolTables, ArrayList<String> errors){

    for(int i = 0; i < this.jjtGetNumChildren(); i++){
      
      this.jjtGetChild(i).analyzeSemantics(symbolTables, errors);
      

    }

  }

}
/* JavaCC - OriginalChecksum=0d5497dff88ce23f07c5aeb55fa638a3 (do not edit this line) */