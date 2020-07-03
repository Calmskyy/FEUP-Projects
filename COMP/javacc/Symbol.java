public class Symbol{

    private String name;
    private String type;
    private boolean initialized;
    private int scope;

    // --- Constructor

    public Symbol(String name, String type, int scope){
        this.name = name;
        this.type = type;
        this.scope = scope;
    }

    public Symbol(String name, String type, int scope, boolean initialized){
        this.name = name;
        this.type = type;
        this.scope = scope;
        this.initialized = initialized;
    }

    // --- Getters

    public String getName(){
        return this.name;
    }

    public String getType(){
        return this.type;
    }

    public int getScope(){
        return this.scope;
    }

    public boolean getInit(){
        return this.initialized;
    }

    // --- Setters

    public void setScope(int scope) {
        this.scope = scope;
    }

    public void initialize() {
        this.initialized = true;
    }


    // --- Override Methods

    public boolean equals(Object symbol) {
        Symbol s = (Symbol) symbol;
        return this.name.equals(s.getName());
    }



}