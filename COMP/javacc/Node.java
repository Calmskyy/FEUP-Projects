/* Generated By:JJTree: Do not edit this line. Node.java Version 6.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=false,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
/* All AST nodes must implement this interface.  It provides basic
   machinery for constructing the parent and child relationships
   between nodes. */
import java.util.ArrayList;
public
interface Node {

  /** This method is called after the node has been made the current
    node.  It indicates that child nodes can now be added to it. */
  public void jjtOpen();

  /** This method is called after all the child nodes have been
    added. */
  public void jjtClose();

  /** This pair of methods are used to inform the node of its
    parent. */
  public void jjtSetParent(Node n);
  public Node jjtGetParent();

  /** This method tells the node to add its argument to the node's
    list of children.  */
  public void jjtAddChild(Node n, int i);

  /** This method returns a child node.  The children are numbered
     from zero, left to right. */
  public Node jjtGetChild(int i);

  /** Return the number of children the node has. */
  public int jjtGetNumChildren();

  public int getId();

  public String getVal();

  public boolean getIsStatic();
  public String getClassName();
  public String getMethodName();
  public String getMethod();
  public void setMethod(String method);
  //public ArrayList<Symbol> getArguments();
  //public void setArguments(ArrayList<Symbol> arguments);

  public void analyzeSemantics(ArrayList<SymbolTable> symbolTables, ArrayList<String> errors);

  public String getCode(ArrayList<SymbolTable> symbolTables, SimpleNode stackMethod);

  public int getIndex();

  public void incrementIndex();

  public void incStack();

  public void decStack();

  public void decStack(int i);

  public void updateMaxStack();

}
/* JavaCC - OriginalChecksum=f321f02c1d43b87914acea48d856de05 (do not edit this line) */