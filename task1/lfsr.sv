module lfsr (
    input logic         clk,
    input logic         rst,
    input logic         en,
    output logic [3:0]       data_out
);
    logic [4:1]     sreg;
    always_ff @(posedge clk)
        if (rst)
            sreg <= 4'b1;
        else if (en) begin
            sreg[4] <= sreg[3];
            sreg[3] <= sreg[2];
            sreg[2] <= sreg[1];
            sreg[1] <= (sreg[3] + sreg[4]);
        end
    assign data_out = sreg;
endmodule
