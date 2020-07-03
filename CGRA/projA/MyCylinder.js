/**
 * MyCylinder
 * @constructor
 * @param scene - Reference to MyScene object
 */
class MyCylinder extends CGFobject {
      constructor(scene, slices) {
            super(scene);
            this.slices = slices;
            this.scene = scene;
            this.initBuffers();
      }
      initBuffers() {
            this.vertices = [];
            this.indices = [];
            this.normals = [];
            this.texCoords = [];

            var ang = 0;
            var alphaAng = 2 * Math.PI / this.slices;

            for (var i = 0; i < this.slices; i++) {

                  var sa = Math.sin(ang);
                  var ca = Math.cos(ang);

                  this.vertices.push(ca, 0, -sa);
                  this.vertices.push(ca, 1, -sa);

                  this.normals.push(ca, 0, -sa);
                  this.normals.push(ca, 0, -sa);

                  this.texCoords.push(i / this.slices, 0);
                  this.texCoords.push(i / this.slices, 1);

                  this.indices.push(2 * i, (2 * i + 2) % (2 * this.slices), (2 * i + 1) % (2 * this.slices));
                  this.indices.push((2 * i + 1) % (2 * this.slices), (2 * i + 2) % (2 * this.slices), (2 * i + 3) % (2 * this.slices));

                  ang += alphaAng;
            }
            this.primitiveType = this.scene.gl.TRIANGLES;
            this.initGLBuffers();
      }

      updateBuffers(complexity) {
            this.slices = 3 + Math.round(9 * complexity); //complexity varies 0-1, so slices varies 3-12

            // reinitialize buffers
            this.initBuffers();
            this.initNormalVizBuffers();
      }
}