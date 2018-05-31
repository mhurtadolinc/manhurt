module scr1(input clk_i, rst_i, input [31:0] address_i, input en_write_i, input en_read_i,input [31:0] data_i, output reg[31:0] data_out_o);

reg [31:0] register[31:0]; // estructura de 18 registros de 32 bits

    always @(posedge clk_i or posedge rst_i) 
    
        if (en_write_i)   begin
        case (address_i) 
            32'b001100000001 : register[32'b00001][31:0] <= data_i; // 1 misa			0x301
        32'b111100010001 : register[32'b00010][31:0] <= data_i; // 2 mvendorid			0xF11
        32'b111100010010 : register[32'b00011][31:0] <= data_i; // 3 marchid			0xF12
        32'b111100010011 : register[32'b00100][31:0] <= data_i; // 4 mimpid 			0xF13
        32'b111100010100 : register[32'b00101][31:0] <= data_i; // 5 mhartid			0xF14
        32'b001101000010 : register[32'b00110][31:0] <= data_i; // 6 mcause				0x342
        32'b001100000000 : register[32'b00111][31:0] <= data_i; // 7 mtatus				0x300
        32'b001100000101 : register[32'b01000][31:0] <= data_i; // 8 mtvec				0x305
        32'b001101000001 : register[32'b01001][31:0] <= data_i; // 9 mepc				0x341
        32'b001101000100 : register[32'b01010][31:0] <= data_i; // 10 mip 				0x344
        32'b001100000100 : register[32'b01011][31:0] <= data_i; // 11 mie 				0x304
        32'b101100000000 : register[32'b01100][31:0] <= data_i; // 12 mcycle 			0xB00
        32'b101110000000 : register[32'b01101][31:0] <= data_i; // 13 mycleh 			0xB80
        32'b101100000010 : register[32'b01110][31:0] <= data_i; // 14 minstret 			0xB02
        32'b101110000010 : register[32'b01111][31:0] <= data_i; // 15 minstreth 		0xB82
        32'b001100000110 : register[32'b10000][31:0] <= data_i; // 16 mcounteren  		0x306
        default;
        endcase 
    end
    
    else if (rst_i) begin
    	register[32'b00001][31:0] <= 0; // 1 misa			    	                    0x301
        register[32'b00010][31:0] <= 0; // 2 mvendorid			                        0xF11
        register[32'b00011][31:0] <= 0; // 3 marchid			                        0xF12
        register[32'b00100][31:0] <= 0; // 4 mimpid 			                        0xF13
        register[32'b00101][31:0] <= 0; // 5 mhartid			                        0xF14
        register[32'b00110][31:0] <= 0; // 6 mcause				                        0x342
        register[32'b00111][31:0] <= 0; // 7 mtatus				                        0x300
        register[32'b01000][31:0] <= 0; // 8 mtvec				                        0x305
        register[32'b01001][31:0] <= 0; // 9 mepc				                        0x341
        register[32'b01010][31:0] <= 0; // 10 mip 				                        0x344
        register[32'b01011][31:0] <= 0; // 11 mie 				                        0x304
        register[32'b01100][31:0] <= 0; // 12 mcycle 			                        0xB00
        register[32'b01101][31:0] <= 0; // 13 mycleh 			                        0xB80
        register[32'b01110][31:0] <= 0; // 14 minstret 			                        0xB02
        register[32'b01111][31:0] <= 0; // 15 minstreth 		                        0xB82
        register[32'b10000][31:0] <= 0; // 16 mcounteren  		                        0x306
    end
    
    else if (en_read_i)   begin
        case(address_i)
        32'b001100000001 : data_out_o <= register[32'b00001]; // 1 misa
        32'b111100010001 : data_out_o <= register[32'b00010]; // 2 mvendorid
        32'b111100010010 : data_out_o <= register[32'b00011]; // 3 marchid
        32'b111100010011 : data_out_o <= register[32'b00100]; // 4 mimpid 
        32'b111100010100 : data_out_o <= register[32'b00101]; // 5 mhartid
        32'b001101000010 : data_out_o <= register[32'b00110]; // 6 mcause
        32'b001100000000 : data_out_o <= register[32'b00111]; // 7 mtatus
        32'b001100000101 : data_out_o <= register[32'b01000]; // 8 mtvec
        32'b001101000001 : data_out_o <= register[32'b01001]; // 9 mepc
        32'b001101000100 : data_out_o <= register[32'b01010]; // 10 mip
        32'b001100000100 : data_out_o <= register[32'b01011]; // 11 mie
        32'b101100000000 : data_out_o <= register[32'b01100]; // 12 mcycle 
        32'b101110000000 : data_out_o <= register[32'b01101]; // 13 mycleh
        32'b101100000010 : data_out_o <= register[32'b01110]; // 14 minstret
        32'b101110000010 : data_out_o <= register[32'b01111]; // 15 minstreth
        32'b001100000110 : data_out_o <= register[32'b10000]; // 16 mcounteren         
        default data_out_o <= 32'b000000000000;
        endcase
    end
endmodule
