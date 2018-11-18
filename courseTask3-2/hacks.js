var ieee754 = require("ieee754");

function formatBinary(val) {
    let str = val.toString(2);
    
    while (str.length < 8) {
    str = "0" + str;
    }
    
    return str;

}

/*const buf = new Uint8Array([
0b00000000,
0b00000000,
0b00000000,
0b00000011
]);*/

const buf = new Uint8Array([
0b01000110,
0b01000000,
0b11100110,
0b10110111
]);

console.log("Hi: ");
console.log(ieee754.read(buf, 0, false, 23, 4));

// 01000110 01000000 11100110 10110111
// 10110111 01000000 11100110 01000110
// const out = Buffer.alloc(4);
const out = new Uint8Array(4);
// const value = 12345.6789;
const value = 12345.6787109375;
ieee754.write(out, value, 0, false, 23, 4);
console.log(formatBinary(out[0]) + " " + formatBinary(out[1]) + " " + formatBinary(out[2]) + " " + formatBinary(out[3]));