/* Generated By:JJTree: Do not edit this line. ASTMethod.java Version 6.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=false,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
import java.util.ArrayList;
public
class ASTMethod extends SimpleNode {

  int maxStack = 0;
  int currentStack = 0;
  int localLimit = 0;

  public ASTMethod(int id) {
    super(id);
  }

  public ASTMethod(Jmm p, int id) {
    super(p, id);
  }

  @Override
  public void analyzeSemantics(ArrayList<SymbolTable> symbolTables, ArrayList<String> errors){

    for(int i = 0; i < this.jjtGetNumChildren(); i++){
      
      this.jjtGetChild(i).setMethod(this.jjtGetChild(1).getVal());
      //this.jjtGetChild(i).setArguments(this.getArguments());
      this.jjtGetChild(i).analyzeSemantics(symbolTables, errors);
    }

  }

  @Override
  public String getCode(ArrayList<SymbolTable> symbolTables, SimpleNode stackMethod){
    
    StringBuilder header = new StringBuilder(".method public ");

    int i = 2;

    
    String type = this.jjtGetChild(0).toString();
    String name = this.jjtGetChild(1).getVal();

    header.append(name + "(");

    if(this.jjtGetNumChildren() > 2 && this.jjtGetChild(2).toString().equals("Args")){

      i++;
      SimpleNode args = (SimpleNode) this.jjtGetChild(2);

      for(int j = 0; j < args.jjtGetNumChildren();j+=2){
                
        String argType = args.jjtGetChild(j).toString();

        if(argType.equals("Int")){
          header.append("I");
        }
        else if(argType.equals("Array")){
          header.append("[I");
        }
        else if(argType.equals("Boolean")){
          header.append("Z");
        }
        else{
          header.append("java/lang/Object");
        }

      }

      header.append(")");

      if(type.equals("Int")){
        header.append("I");
      }
      else if(type.equals("Array")){
        header.append("[I");
      }
      else if(type.equals("Boolean")){
        header.append("Z");
      }
      else{
        header.append("java/lang/Object");
      }

    }

    for(int k = 0; k < symbolTables.size(); k++ ){
      if(symbolTables.get(k).getName().equals(this.jjtGetChild(1).getVal())){
        localLimit = symbolTables.get(k).getVariables().size() + symbolTables.get(k).getArguments().size();
      }
    }    

    StringBuilder code = new StringBuilder("");

    for(; i < this.jjtGetNumChildren(); i++){
      
      this.jjtGetChild(i).setMethod(this.jjtGetChild(1).getVal());
      code.append(this.jjtGetChild(i).getCode(symbolTables, this));

    }

    code.append(".end method\n");

    StringBuilder limits = new StringBuilder("\n");

    String localLimitString = Integer.toString(localLimit + 1); 

    // STACK
    limits.append(".limit stack " + maxStack + "\n");
    limits.append(".limit locals " + localLimitString + "\n");
    // limits.append(".limit stack 99\n");
    // limits.append(".limit locals 99\n");
    
    return header.toString() + limits.toString() + code.toString();

  }

  public void incStack(){
    this.currentStack++;
  }

  public void decStack(){
    this.currentStack--;
  }

  public void decStack(int i){
    this.currentStack -= i;
  }

  public void updateMaxStack(){
    if(this.currentStack > this.maxStack){
      this.maxStack = this.currentStack;
    }
  }

}
/* JavaCC - OriginalChecksum=731f9bf0fdf8d850953657393beb871c (do not edit this line) */
