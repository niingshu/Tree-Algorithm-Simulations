const canvas = document.getElementById("graph");
const ctx = canvas.getContext("2d");

export function clearCanvas() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
}

export function drawNode(ctx, x, y, radius, fill, stroke, strokeWidth, id) {
    ctx.beginPath();
    //arc (x,y,radius, startAngle, endAngle, anticlockwise)
    ctx.arc(x,y,radius, 0, 2*Math.PI, false);
    //2*math.pi draws a full circle

    if (fill) {
        ctx.fillStyle = fill;
        ctx.fill();
    }

    if (stroke) {
        ctx.lineWidth = strokeWidth;
        ctx.strokeStyle = stroke;
        ctx.stroke();
    }

    //draw the id of the node on itself
    ctx.fillStyle = "white";
    ctx.font = "14px Arial";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText(id,x,y);

}