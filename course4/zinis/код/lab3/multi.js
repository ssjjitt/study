const elementary_alphabet = ["А", "Б", "В", "Г", "Д", "Дж", "Дз", "Е", "Ё", "Ж", "І", "Й", "К", "Л", "М",
    "Н", "О", "П", "Р", "С", "Т", "У", "Ў", "Ф", "Х", "Ц", "Ч", "Ш", "Ы", "Ь",
    "Э", "Ю", "Я", "'", " ", "."]


const key1 = "глухава";
const key2 = "дар'я";


function sortMatrix(matrix) {
    const header = matrix[0].slice(1); 
    const rowHeader = matrix.slice(1).map(row => row[0]); 
  
    const sortedColumnIndices = [...header].map((value, index) => ({ value, index }))
      .sort((a, b) => a.value.localeCompare(b.value))
      .map(item => item.index);
    
    matrix.forEach(row => {
      let newRow = row.slice(0, 1); 
      sortedColumnIndices.forEach(index => {
        newRow.push(row[index + 1]); 
      });
      row.length = 0;
      row.push(...newRow);
    });
  
    
    return matrix;
  }

function readMatrixWithoutHeaders(matrix) {
    let result = [];
    for (let i = 1; i < matrix.length; i++) {
      result.push(...matrix[i].slice(1));
    }
    return result.join(''); 
  }
  

function code(text){
    const text_size = text.length

    const arr = text.split('')
    const key1 = "глухава"
    const key2 = "дар'я"

    const key1_length = key1.length
    const key2_length = key2.length

    const cols = key1_length
    let rows
    let repeat = 1
    if(text_size > key1_length * key2_length){
        repeat = Math.floor(Math.floor(text_size / key1_length) / key2_length) + 1 
        rows = repeat * key2_length
    } else if(text_size == key1_length * key2_length){
        rows = text_size / key2_length
    } else if(text_size < key1_length * key2_length){
        rows = Math.floor(text_size / key2_length) + 1
    }

    //console.log(rows, cols);

    let matrix = []

    matrix.push(('#'+key2.repeat(repeat)).split(''))

    let temp_arr = []
    for(let i = 0; i != cols * rows ; i++){
        if(i % rows == 0){
            temp_arr.push(key1[i / rows])
        }
        if(arr[i] == undefined)
            temp_arr.push('$')
        else
            temp_arr.push(arr[i])
        
        if(temp_arr.length == cols + 1) {
            matrix.push(temp_arr)
            temp_arr = []
        }
    }

    matrix = sortMatrix(matrix)
    
    return readMatrixWithoutHeaders(matrix)
}

function getSortedIndices(header) {
  return [...header].map((value, index) => ({ value, index }))
    .sort((a, b) => a.value.localeCompare(b.value))
    .map(item => item.index);
}

function sortColumnsByFirstRow(matrix) {
    let firstRow = matrix[0];
  
    let columnIndices = firstRow.map((value, index) => ({ index, value }));
        
    columnIndices.sort((a, b) => a.value - b.value);
    
    let sortedMatrix = [];
  
    for (let i = 0; i < matrix.length; i++) {
      let sortedRow = columnIndices.map(column => matrix[i][column.index]);
      sortedMatrix.push(sortedRow);
    }
  
    return sortedMatrix;
  }

function decode(shifr){
    const text_size = shifr.length

    const arr = shifr.split('')
    const key1 = "глухава"
    const key2 = "дар'я"

    const key1_length = key1.length
    const key2_length = key2.length

    const cols = key1_length
    let rows
    let repeat = 1
    if(text_size > key1_length * key2_length){
        repeat = Math.floor(Math.floor(text_size / key1_length) / key2_length) + 1 
        rows = repeat * key2_length
    } else if(text_size == key1_length * key2_length){
        rows = text_size / key2_length
    } else if(text_size < key1_length * key2_length){
        rows = Math.floor(text_size / key2_length) + 1
    }

    let matrix = []

    const shifr_arr = shifr.split('')
    const sorted_key1 = key1
    const sorted_key2 = key2.repeat(repeat).split('').sort()

    sorted_key2.unshift('#')
    matrix.push(sorted_key2)

    let temp_arr = []
    for(let i = 0; i != cols * rows ; i++){
        if(i % rows == 0){
            temp_arr.push(sorted_key1[i / rows])
        }
        if(shifr_arr[i] == undefined)
            temp_arr.push('$')
        else
            temp_arr.push(shifr_arr[i])
        
        if(temp_arr.length == cols + 1) {
            matrix.push(temp_arr)
            temp_arr = []
        }
    }


    let m = []
    m.push(sorted_key2)
    let temp = []
    let temp_key2 = [...key2.repeat(repeat)]

    for(let i = 1; i <= rows; i++){
        let index = temp_key2.indexOf(sorted_key2[i])
        
        temp.push(index)
        temp_key2[index] = '@'
    }
    m.push(temp)

    
    for(let i = 1; i <= m[1].length; i++){
        matrix[0][i] = m[1][i-1]
    }

    matrix = sortColumnsByFirstRow(matrix)

    return readMatrixWithoutHeaders(matrix)    
}

module.exports = { codeMulti: code, decodeMulti: decode };
