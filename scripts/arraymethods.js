//
// Some handy array methods
//
var fruits = ['Apple', 'Apricot', 'Avocado', 'Banana', 'Bilberry', 'Blackberry',
    'Blackcurrant', 'Blueberry', 'Boysenberry', 'Blood Orange', 'Watermelon'
]
console.log(`----- fruits and index with forEach -----`)
fruits.forEach((item, index) => {
    console.log(item, index)
})

// add some more fruit
fruits.push('Honeydew', 'Huckleberry')
console.log(`----- new elements added with push, fruits and index with map -----`)
fruits.map((item, index) => {
    console.log(item, index)
})

// create a new berry array filtering fruit
var berries = fruits.filter((fruit) => fruit.indexOf('berry') > 0)
console.log(`----- new berries array -----`)
berries.map((item) => {
    console.log(item)
})

// remove the first element (Bilberry) from berries using shift
berries.shift()
console.log(`----- berries without Bilberry -----`)
berries.map((item) => {
    console.log(item)
})

// add Eldeberry to the front of the array using unshift
berries.unshift('Eldeberry')
console.log(`----- berries with Eldeberry at the front -----`)
berries.map((item) => {
    console.log(item)
})

// remove Boysenberry from the array
var i = berries.indexOf("Boysenberry");
if(i != -1) {
    berries.splice(i, 1)
}
console.log(`----- berries without Boysenberry element -----`)
berries.map((item) => {
    console.log(item)
})

// create a non-berry array using the filter again
var noberries = fruits.filter((fruit) => fruit.indexOf('berry') === -1)
console.log(`----- noberries -----`)
noberries.map((item) => {
    console.log(item)
})

// merge both arrays using spread operator
var someberries = [...berries, ...noberries]
console.log(`----- someberries -----`)
someberries.map((item) => {
    console.log(item)
})

// alternative to push using spread operator
berries = [...berries, 'Strawberry']
console.log(`----- updated berries using spread operator -----`)
berries.map((item) => {
    console.log(item)
})

var bloodFruit = fruits.find((fruit) => fruit.includes('Blood'))
console.log(`----- Fruit that contains 'blood' -----`)
console.log(bloodFruit)
