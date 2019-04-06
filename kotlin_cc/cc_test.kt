// kotlinc cc_test.kt -include-runtime -d cc_test_Kt.jar
// jar files must end with Kt

// java -jar cc_test_Kt.jar

fun main(args: Array<String>) {
    println("====== Cut Calculator Kotlin Tests ======")

    val tests = HashMap<String, String>()

    tests.put("has_bit()",            "Not Complete")
    tests.put("flip_bit()",           "Not Complete")
    tests.put("has_common_bit()",     "Not Complete")
    tests.put("next_binary()",        "Not Complete")
    tests.put("skip_binary()",        "Not Complete")
    tests.put("to_binary()",          "Not Complete")
    tests.put("to_integer()",         "Not Complete")
    tests.put("set_inputs()",         "Not Complete")
    tests.put("combo_size()",         "Not Complete")
    tests.put("build_piece_combos()", "Not Complete")
    tests.put("filter_pieces()",      "Not Complete")
    tests.put("best_match()",         "Not Complete")
    tests.put("remove_combos()",      "Not Complete")
    tests.put("test_sort()",          "Not Complete")

    
    var spaces = 0
    for((key, value) in tests)
        spaces = if (key.length > spaces) key.length else spaces
        

    println("\nSummary")
    for((key, value) in tests)
        println("${key.padStart(spaces)}: $value")
}