//* Nesting multi-line comments
/**
 * - we cannot nest multi-line comments!
 * - build error appears triggered by [Wcomment] compiler warning flag
 */

int main()
{
    /* 1. Multi-line comment
     * ...
        /* 2. Multi-line comment 
         * ...
        */
     */

    return 0;
}