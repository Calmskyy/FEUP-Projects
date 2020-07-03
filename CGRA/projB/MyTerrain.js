class MyTerrain extends CGFobject {
    constructor(scene) {
        super(scene);
        this.scene = scene;
        this.initBuffers();

        this.plane = new Plane(this.scene, 32);

        this.terrainTexture = new CGFtexture(this.scene, "images/terrain.jpg");
        this.mapTexture = new CGFtexture(this.scene, "images/editedmap.png");
        this.gradientTexture = new CGFtexture(this.scene, "images/altimetry.png");

        this.terrainAppearance = new CGFappearance(this.scene);
        this.terrainAppearance.setAmbient(0, 0, 0, 1);
        this.terrainAppearance.setDiffuse(0.9, 0.9, 0.9, 1);
        this.terrainAppearance.setSpecular(0, 0, 0, 1);
        this.terrainAppearance.setShininess(10.0);
        this.terrainAppearance.setTexture(this.terrainTexture);
        this.terrainAppearance.setTextureWrap('REPEAT', 'REPEAT');

        this.shader = new CGFshader(this.scene.gl, "shaders/myTerrain.vert", "shaders/myTerrain.frag");
        this.shader.setUniformsValues({ uSampler: 1 });
        this.shader.setUniformsValues({ uSampler2: 2 });
        this.shader.setUniformsValues({ uSampler3: 3 });
    }
    display() {
        this.terrainAppearance.apply();
        this.scene.setActiveShader(this.shader);

        this.terrainTexture.bind(1);
        this.mapTexture.bind(2);
        this.gradientTexture.bind(3);

        this.plane.display();
    }
}