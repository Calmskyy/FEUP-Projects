/**
* MyInterface
* @constructor
*/
class MyInterface extends CGFinterface {
    constructor() {
        super();
    }

    init(application) {
        // call CGFinterface init
        super.init(application);
        // init GUI. For more information on the methods, check:
        // http://workshop.chromeexperiments.com/examples/gui
        this.gui = new dat.GUI();
        
        var obj = this;

        //Checkbox element in GUI
        this.gui.add(this.scene, 'displayAxis').name('Display Axis');

        this.gui.add(this.scene, 'displayTangram').name('Display Tangram');

        this.gui.add(this.scene, 'displayCube').name('Display Cube');

      //  this.gui.add(this.scene, 'displayDiamond').name('Display Diamond');

      //  this.gui.add(this.scene, 'displayTriangle').name('Display Triangle');

      //  this.gui.add(this.scene, 'displayParal').name('Display Paral');

      //  this.gui.add(this.scene, 'displayTriangleSmall').name('Display Small T');

      //  this.gui.add(this.scene, 'displayTriangleBig').name('Display Big T');

      //  this.gui.add(this.scene, 'displayTriangleSmall2').name('Display Small T 2');

       // this.gui.add(this.scene, 'displayTriangleBig2').name('Display Big T 2');

        //Slider element in GUI
        this.gui.add(this.scene, 'scaleFactor', 0.1, 5).name('Scale Factor');

        return true;
    }
}