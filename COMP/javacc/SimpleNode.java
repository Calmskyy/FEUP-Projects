/* Generated By:JJTree: Do not edit this line. SimpleNode.java Version 6.1 */
/* JavaCCOptions:MULTI=false,NODE_USES_PARSER=false,VISITOR=false,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
import java.util.ArrayList;
public
class SimpleNode implements Node {

  protected Node parent;
  protected Node[] children;
  protected int id;
  protected Object value;
  protected Jmm parser;
  protected String val;

  protected boolean isStatic;
  protected String className; 
  protected String methodName;

  protected String method = "global";
  protected int statementIndex = 0;

  public SimpleNode(int i) {
    id = i;
  }

  public SimpleNode(Jmm p, int i) {
    this(i);
    parser = p;
  }

  public void jjtOpen() {
  }

  public void jjtClose() {
  }

  public void jjtSetParent(Node n) { parent = n; }
  public Node jjtGetParent() { return parent; }

  public void jjtAddChild(Node n, int i) {
    if (children == null) {
      children = new Node[i + 1];
    } else if (i >= children.length) {
      Node c[] = new Node[i + 1];
      System.arraycopy(children, 0, c, 0, children.length);
      children = c;
    }
    children[i] = n;
  }

  public Node jjtGetChild(int i) {
    return children[i];
  }

  public int jjtGetNumChildren() {
    return (children == null) ? 0 : children.length;
  }

  public void jjtSetValue(Object value) { this.value = value; }
  public Object jjtGetValue() { return value; }

  /* You can override these two methods in subclasses of SimpleNode to
     customize the way the node appears when the tree is dumped.  If
     your output uses more than one line you should override
     toString(String), otherwise overriding toString() is probably all
     you need to do. */

  public String toString() {
    return JmmTreeConstants.jjtNodeName[id];
  }
  public String toString(String prefix) { return prefix + toString(); }

  /* Override this method if you want to customize how the node dumps
     out its children. */

  public void dump(String prefix) {
    System.out.println(toString(prefix));
    if(children == null && this.val != null)
      System.out.println(prefix + "\t[ "+this.val+" ]");
    if (children != null) {
      for (int i = 0; i < children.length; ++i) {
        SimpleNode n = (SimpleNode)children[i];
        if (n != null) {
          n.dump(prefix + "  ");
        }
      }
    }
  }

  public int getId() {
    return id;
  }

  public String getVal() { return this.val; }

  public boolean getIsStatic() { return this.isStatic; }

  public String getClassName() { return this.className; }

  public String getMethodName() { return this.methodName; }

  public String getMethod() { return this.method; }

  public void setMethod(String method) { this.method = method; }

  // This method is called recursively from the root node to all of its children. 
  // Its overrode on different instances of AST files.
  public void analyzeSemantics(ArrayList<SymbolTable> symbolTables, ArrayList<String> errors){
    System.out.println("Oh no!");
  }

  // This method is called recursively from the root node to all of its children. 
  // Its overrode on different instances of AST files. 
  public String getCode(ArrayList<SymbolTable> symbolTables, SimpleNode stackMethod){
    return "; something is missing here\n";
  }
  
  public int getIndex(){
    return this.statementIndex;
  }

  public void incrementIndex(){
    this.statementIndex++;
  }

  public void incStack(){}

  public void decStack(){}

  public void decStack(int i){}

  public void updateMaxStack(){}

}

/* JavaCC - OriginalChecksum=d33fdb2b8063d5de3474649324d5d160 (do not edit this line) */
