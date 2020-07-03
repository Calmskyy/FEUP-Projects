/* Generated By:JJTree: Do not edit this line. ASTAssign.java Version 4.3 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=false,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
import java.util.ArrayList;

public
class ASTAssign extends SimpleNode {
  public ASTAssign(int id) {
    super(id);
  }

  public ASTAssign(Jmm p, int id) {
    super(p, id);
  }

  @Override
  public void analyzeSemantics(ArrayList<SymbolTable> symbolTables, ArrayList<String> errors){
   

    for(int i = 0; i < this.jjtGetNumChildren(); i++){
      
      this.jjtGetChild(i).setMethod(this.getMethod());
      this.jjtGetChild(i).analyzeSemantics(symbolTables, errors);
    }

    SymbolTable st = null;
    for (int i = 0; i < symbolTables.size(); i++) {
      if (symbolTables.get(i).getName().equals(this.getMethod())) 
        st = symbolTables.get(i);
    }
    if (st == null)
      return;
  
    SimpleNode first_operand = (SimpleNode) this.jjtGetChild(0);
    SimpleNode second_operand = (SimpleNode) this.jjtGetChild(1);
    String first_operand_name = "";
    String second_operand_name = "";
    String first_operand_type = "";
    String second_operand_type = "";
    boolean verificationWithExpressions1st = true;
    boolean verificationWithExpressions2st = true;

    //############### First Child ###############
    if (first_operand.toString().equals("Identifier")) {
      verificationWithExpressions1st = false;
      first_operand_name = first_operand.getVal();
    if (!st.hasVariable(first_operand_name)) {
        boolean missingVariable = true;

        for(int i=0; i<symbolTables.size();i++){ //checking if it's a field variable
          if(symbolTables.get(i).getClassSpecific()){
            if(symbolTables.get(i).hasVariable(first_operand_name)){
              missingVariable = false;
              first_operand_type = symbolTables.get(i).getType(first_operand_name);
              symbolTables.get(i).initVariable(first_operand_name);
            }
          }
        }

        if(missingVariable){
          errors.add("ERROR: ASSIGN includes a variable that does not exist: " + first_operand_name + ".");
          return;
        }
      }
    }
    else if (first_operand.toString().equals("Value")) {
      verificationWithExpressions1st = false;
      if (first_operand.getVal() == "true" || first_operand.getVal() == "false")
        first_operand_type = "Boolean";
      else
        first_operand_type = "Int";
    }
    else if (first_operand.toString().equals("FunctionCall")) {
      first_operand_name = first_operand.jjtGetChild(1).getVal();
      for (int a = 0; a < symbolTables.size(); a++) {
        if (symbolTables.get(a).getClassSpecific()) {
          for (int j = 0; j < symbolTables.get(a).getMethods().size(); j++) {
            if (symbolTables.get(a).getMethods().get(j).getName().equals(first_operand_name))
              first_operand_type = symbolTables.get(a).getMethods().get(j).getType();
          }
        }
      }
      if (first_operand_type.equals("")) { //check imports
        for (int a = 0; a < symbolTables.size(); a++) {
          for (int j = 0; j < symbolTables.get(a).getImports().size(); j++) {
            if (symbolTables.get(a).getImports().get(j).get("methodName").get(0) != null) {
              if (symbolTables.get(a).getImports().get(j).get("methodName").get(0).equals(first_operand_name)) {
                first_operand_type = symbolTables.get(a).getImports().get(j).get("returnType").get(0);
              }
            }
          }
        }
      }
      if (first_operand_type.equals("")) {
        errors.add("ERROR: AND includes a function call that does not exist: " + first_operand_name + ".");
        return;
      }       
    }
    else if (first_operand.toString() == "Sum" || first_operand.toString() == "Sub" || first_operand.toString() == "Mult" ||
    first_operand.toString() == "Div" || first_operand.toString() == "Dot" || first_operand.toString() == "ArrayAccess") {
      first_operand_type = "Int";
    }

    //############### Second Child ###############
    if (second_operand.toString().equals("Identifier")) {
      verificationWithExpressions2st = false;
      second_operand_name = second_operand.getVal();
      if (!st.hasVariable(second_operand_name)) {
        boolean missingVariable = true;

        for(int i=0; i<symbolTables.size();i++){ //checking if it's a field variable
          if(symbolTables.get(i).getClassSpecific()){
            if(symbolTables.get(i).hasVariable(second_operand_name)){
              missingVariable=false;
              second_operand_type = symbolTables.get(i).getType(second_operand_name);
            }
          }
        }

        if(missingVariable){
          errors.add("ERROR: ASSIGN includes a variable that does not exist" +  second_operand_name + ".");
          return;
        }
      }
    }
    else if (second_operand.toString().equals("Value")) {
      verificationWithExpressions2st = false;
      if (second_operand.getVal() == "true" || second_operand.getVal() == "false")
        second_operand_type = "Boolean";
      else
        second_operand_type = "Int";
    }else if(second_operand.toString().equals("NewArray")){
      verificationWithExpressions2st = false;
      second_operand_type = "NewArray";
    }
    else if (second_operand.toString().equals("FunctionCall")) {
      second_operand_name = second_operand.jjtGetChild(1).getVal();
      for (int a = 0; a < symbolTables.size(); a++) {
        if (symbolTables.get(a).getClassSpecific()) {
          for (int j = 0; j < symbolTables.get(a).getMethods().size(); j++) {
            if (symbolTables.get(a).getMethods().get(j).getName().equals(second_operand_name))
              second_operand_type = symbolTables.get(a).getMethods().get(j).getType();
          }
        }
      }
      if (second_operand_type.equals("")) { //check imports
        for (int a = 0; a < symbolTables.size(); a++) {
          for (int j = 0; j < symbolTables.get(a).getImports().size(); j++) {
            if (symbolTables.get(a).getImports().get(j).get("methodName").get(0) != null) {
              if (symbolTables.get(a).getImports().get(j).get("methodName").get(0).equals(second_operand_name)) {
                second_operand_type = symbolTables.get(a).getImports().get(j).get("returnType").get(0);
              }
            }
          }
        }
      }
      if (second_operand_type.equals("")) {
        errors.add("ERROR: Assign includes a function call that does not exist: " + second_operand_name + ".");
        return;
      }       
    }
    else if (second_operand.toString() == "Sum" || second_operand.toString() == "Sub" || second_operand.toString() == "Mult" ||
    second_operand.toString() == "Div" || second_operand.toString() == "Dot" || second_operand.toString() == "ArrayAccess") {
      second_operand_type = "Int";
    }
    else if (second_operand.toString() == "And" || second_operand.toString() == "Less" || second_operand.toString() == "Not")
      second_operand_type = "Boolean";
    else if (second_operand.toString() == "NewClass") {
      second_operand_type = second_operand.jjtGetChild(0).getVal();
    }

    //############### Getting types from local variables ###############
    for (int j = 0; j < st.getVariables().size(); j++) {
      if (first_operand_type.equals("") && st.getVariables().get(j).getName().equals(first_operand_name)) {
        first_operand_type = st.getVariables().get(j).getType();
        st.getVariables().get(j).initialize();
      }
      if (second_operand_type.equals("") && st.getVariables().get(j).getName().equals(second_operand_name)) {
        second_operand_type = st.getVariables().get(j).getType();
      }
    }
    //############### Getting types from arguments ###############
    for (int j = 0; j < st.getArguments().size(); j++) {
      if (first_operand_type.equals("") && st.getArguments().get(j).getName().equals(first_operand_name)) {
        first_operand_type = st.getArguments().get(j).getType();
      }
      if (second_operand_type.equals("") && st.getArguments().get(j).getName().equals(second_operand_name)) {
        second_operand_type = st.getArguments().get(j).getType();
      }
    }
    if (first_operand_type.equals("") || second_operand_type.equals("")) {
      errors.add("ERROR: Incompatible Assign using a " + first_operand.toString() + " and a " + second_operand.toString() + ".");
      return;
    }

    //test if the two operands are of different types
    if(verificationWithExpressions1st == false && verificationWithExpressions2st == false){
      if(!(first_operand_type.equals("Array") && second_operand_type.equals("NewArray"))){
        if (!first_operand_type.equals(second_operand_type)){
          errors.add("ERROR: Incompatible ASSIGN using " + first_operand_type + " and " + second_operand_type + ".");
          return;
        }
      }else{
        if(second_operand.jjtGetChild(0).toString().equals("Value") && (second_operand.jjtGetChild(0).getVal() == "true" || second_operand.jjtGetChild(0).getVal() == "false" || second_operand.jjtGetChild(0).getVal() == "this")){
          errors.add("ERROR: Incompatible ASSIGN, creating new array " + first_operand_name + " without using an integer between brackets.");
          return;
        }else if(second_operand.jjtGetChild(0).toString().equals("Identifier")){
          String no = second_operand.jjtGetChild(0).getVal();
          String no_type = "";

          if (!st.hasVariable(no)) {
            boolean missingVariable = true;
    
            for(int i=0; i<symbolTables.size();i++){ //checking if it's a field variable
              if(symbolTables.get(i).getClassSpecific()){
                if(symbolTables.get(i).hasVariable(no)){
                  missingVariable = false;
                  no_type = symbolTables.get(i).getType(no);
                }
              }
            }
    
            if(missingVariable){
              errors.add("ERROR: ASSIGN includes a variable that does not exist [NewArray initialization]: " + no + ".");
              return;
            }
          }

          //############### Getting types from local variables ###############
          for (int j = 0; j < st.getVariables().size(); j++) {
            if (first_operand_type.equals("") && st.getVariables().get(j).getName().equals(no)) {
              no_type = st.getVariables().get(j).getType();
            }
          }
          //############### Getting types from arguments ###############
          for (int j = 0; j < st.getArguments().size(); j++) {
            if (first_operand_type.equals("") && st.getArguments().get(j).getName().equals(no)) {
              no_type = st.getArguments().get(j).getType();
            }
          }
        
          if(!no_type.equals("Int")){
            errors.add("ERROR: Incompatible ASSIGN, creating new array " + first_operand_name + " without using an integer between brackets.");
            return;
          }
        }
      }
    }
  }

  @Override
  public String getCode(ArrayList<SymbolTable> symbolTables, SimpleNode stackMethod){
    
    StringBuilder code = new StringBuilder("");

    if(this.jjtGetNumChildren() == 2){

      SimpleNode first_child = (SimpleNode) this.jjtGetChild(0);
      SimpleNode second_child = (SimpleNode) this.jjtGetChild(1);

      if(first_child.toString().equals("ArrayAccess")){

        int first_variable_index = 0;

        for(int i = 0; i < symbolTables.size(); i++){

          if(symbolTables.get(i).getName().equals(this.method) || symbolTables.get(i).getName().equals("global")){

            for(int j = 0; j < symbolTables.get(i).getArguments().size(); j++){
              if(symbolTables.get(i).getArguments().get(j).getName().equals(first_child.jjtGetChild(0).getVal())){
                first_variable_index = j + 1;
              }
            }

            for(int j = 0; j < symbolTables.get(i).getVariables().size(); j++){

              if(symbolTables.get(i).getVariables().get(j).getName().equals(first_child.jjtGetChild(0).getVal())){

                if(this.method.equals("main")){
                  first_variable_index = j + 1;
                }
                else{
                  first_variable_index = symbolTables.get(i).getArguments().size() + j + 1;
                }

              }

            }

          }

        }

        code.append("aload " + first_variable_index + "\n");
        stackMethod.incStack();
        stackMethod.updateMaxStack();

        if(first_child.jjtGetChild(1).toString().equals("Identifier")){

          String value =  first_child.jjtGetChild(1).getVal();

          int second_variable_index = 0;

          for(int i = 0; i < symbolTables.size(); i++){

            if(symbolTables.get(i).getName().equals(this.method) || symbolTables.get(i).getName().equals("global")){

              for(int j = 0; j < symbolTables.get(i).getArguments().size(); j++){
                if(symbolTables.get(i).getArguments().get(j).getName().equals(value)){
                  second_variable_index = j + 1;
                }
              }

              for(int j = 0; j < symbolTables.get(i).getVariables().size(); j++){

                if(symbolTables.get(i).getVariables().get(j).getName().equals(value)){

                  if(this.method.equals("main")){
                    second_variable_index = j + 1;
                  }
                  else{
                    second_variable_index = symbolTables.get(i).getArguments().size() + j + 1;
                  }

                }

              }

            }

          }

          code.append("iload " + second_variable_index + "\n");

        }
        else{
          code.append("bipush " + first_child.jjtGetChild(1).getVal() + "\n");
          stackMethod.incStack();
          stackMethod.updateMaxStack();
        }


      }

      
      switch (second_child.toString()){
        
        case "Sum":
          second_child.setMethod(this.method);
          code.append(second_child.getCode(symbolTables, stackMethod));
          break;
        case "Sub":
          second_child.setMethod(this.method);
          code.append(second_child.getCode(symbolTables, stackMethod));
          break;
        case "Mult":
          second_child.setMethod(this.method);
          code.append(second_child.getCode(symbolTables, stackMethod));
          break;
        case "Div":
          second_child.setMethod(this.method);
          code.append(second_child.getCode(symbolTables, stackMethod));
          break;
        case "Value":
          if(second_child.getVal().equals("true")){
            code.append("bipush 1\n");
          }
          else if(second_child.getVal().equals("false")){
            code.append("bipush 0\n");
          }
          else{
            code.append("bipush " + second_child.getVal() + "\n");
          }
          stackMethod.incStack();
          stackMethod.updateMaxStack();
          break;
        case "NewClass":
          code.append(second_child.getCode(symbolTables, stackMethod));
          break;
        case "FunctionCall":
          code.append(second_child.getCode(symbolTables, stackMethod));
          break;
        case "NewArray":
          code.append(second_child.getCode(symbolTables, stackMethod));
          break;
        case "ArrayAccess":
          code.append(second_child.getCode(symbolTables, stackMethod));
          break;
        case "Dot":
          code.append(second_child.getCode(symbolTables, stackMethod));
          break;
        default:
          code.append("");
      }
      
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

      if(first_child.toString().equals("ArrayAccess")){
        code.append("iastore\n");
        stackMethod.decStack();
      }
      else{
        if(variable_type.equals("Int")){
          code.append("istore " + variable_index + "\n");
          stackMethod.decStack();
        }
        else{
          // TO DO: add other types
          code.append("astore " + variable_index + "\n");
          stackMethod.decStack();
        }
      }
      

      

    }
    
    return code.toString();

  }

}
/* JavaCC - OriginalChecksum=e13fa3f2ab24c4a1bc71c2df2fb54da7 (do not edit this line) */
