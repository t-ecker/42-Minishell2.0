#include "../../includes/minishell.h"

const char* ast_type_to_string(t_astNodeType type) {
    switch (type) {
        case AST_COMMAND: return "COMMAND";
        case AST_PIPE: return "PIPELINE";
        case AST_LOGICAL_OP: return "LOGICAL_OP";
        case AST_SUBSHELL: return "SUBSHELL";
        default: return "UNKNOWN";
    }
}

const char* redirect_type_to_string(t_redirectType type) {
    switch (type) {
        case REDIR_INPUT: return "INPUT (<):";
        case REDIR_OUTPUT: return "OUTPUT (>):";
        case REDIR_APPEND: return "APPEND (>>):";
        case REDIR_HEREDOC: return "HEREDOC (<<):";
        case REDIR_ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

void print_indent(int depth) {
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
}

void print_ast(t_astNode *node, int depth)
{
    if (!node) {
        print_indent(depth);
        printf("NULL\n");
        return;
    }
    
    print_indent(depth);
    printf("%s: ", ast_type_to_string(node->type));
    
    switch (node->type) {
        case AST_COMMAND: {
            t_commandNode *cmd = &node->u_data.command;
            if (cmd->args) {
                printf("%s", cmd->args->value ? cmd->args->value : "(null)");
            } else {
                printf("(no args)");
            }
            printf("\n");
            
            if (cmd->args && cmd->args->next) {
                print_indent(depth + 1);
                printf("Args: ");
                t_argList *arg = cmd->args->next;
                while (arg) {
                    printf("%s%s", arg->value ? arg->value : "", 
                           arg->next ? " " : "");
                    arg = arg->next;
                }
                printf("\n");
            }
            
            if (cmd->redirects) {
                t_redirectList *redirect = cmd->redirects;
                while (redirect) {
                    print_indent(depth + 1);
                    printf("Redirect: %s %s\n", 
                           redirect_type_to_string(redirect->type),
                           redirect->target ? redirect->target : "");
                    redirect = redirect->next;
                }
            }
            break;
        }
        
        case AST_PIPE: {
            t_pipelineNode *pipeline = &node->u_data.pipeline;
            size_t count = 0;
            t_pipelineList *cmd_node = pipeline->commands;
            while (cmd_node) {
                count++;
                cmd_node = cmd_node->next;
            }
            printf("(%zu commands)\n", count);
            
            t_pipelineList *current = pipeline->commands;
            while (current) {
                print_ast(current->command, depth + 1);
                current = current->next;
            }
            break;
        }
        
        case AST_LOGICAL_OP: {
            t_logicalOpNode *binop = &node->u_data.logical_op;
            printf("%s\n", binop->op_type == LOG_OP_AND ? "&&" : "||");
            print_indent(depth + 1);
            printf("Left:\n");
            print_ast(binop->left, depth + 2);
            print_indent(depth + 1);
            printf("Right:\n");
            print_ast(binop->right, depth + 2);
            break;
        }
        
        case AST_SUBSHELL: {
            printf("\n");
            print_ast(node->u_data.subshell.child, depth + 1);
            break;
        }
    }
}