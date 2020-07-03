class MyLightning extends MyLSystem {
    constructor(scene) {
        super(scene);
    }
    initGrammar() {
        this.grammar = {
            "F": new MyQuad2(this.scene),
            "X": new MyQuad2(this.scene)
        };
    };

    iterate() {
        var i, j;
        for (i = 0; i < this.iterations; ++i) {
            var newString = "";

            // substitui cada um dos caracteres da cadeia de caracteres de acordo com as produções
            for (j = 0; j < this.axiom.length; ++j) {
                var axiomProductions = this.productions[this.axiom[j]];
                // aplicar producoes
                if (axiomProductions === undefined) {
                    // caso nao se aplique nenhuma producao deixa estar o caracter original
                    newString += this.axiom[j];
                } else if (axiomProductions.length == 1) {
                    // caso apenas exista uma producao, aplica-a
                    newString += axiomProductions[0];
                } else {
                    // sistema estocastico - varias producoes sao aplicaveis - seleciona aleatoriamente
                    newString += axiomProductions[Math.floor(Math.random() * axiomProductions.length)];
                }
            }

            this.axiom = newString;
        }
        console.log("Final: " + this.axiom);
        console.log("(length: " + this.axiom.length + ")");
    }
}