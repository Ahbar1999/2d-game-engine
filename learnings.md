If you working with a perspective you cannot map pixel coordinates directly to NDC or screen coords,
You cant just pass the position of what it would on the screen to transformation matrices.
In perspective projection you need to account for depth which changes size of the objects depending on distance from camera.
In orthographic projection the size remains constant so we could map the pixel coords to ndc coords directly.