/* Deliberate syntax error: shows that parcc refuses to link
   when one of the parallel compilations fails. */
int helper(int x)
{
    return x * 2   /* missing semicolon */
}
