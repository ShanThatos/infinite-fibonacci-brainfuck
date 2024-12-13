#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint8_t read() {
	int temp = getchar();
	return (uint8_t)(temp != EOF ? temp : 0);
}

static int BLOCK_SIZE = 9;
static int dbg_count = 100000;
static void dbg(uint8_t mem[], uint8_t *p) {
	printf("\nDBG OUTPUT:\n");
	int i, j;
	for (i = 1000; i < 1100; i += BLOCK_SIZE) {
		for (j = 0; j < BLOCK_SIZE; j++) {
			if (p == &mem[i + j])
				printf("*%3d ", mem[i + j]);
			else
				printf(" %3d ", mem[i + j]);
		}
		printf("\n");
	}
	if (--dbg_count == 0)
		exit(0);
}
int main(void) {
	uint8_t mem[1000000] = {0};
	uint8_t *p = &mem[1000];
	uint8_t dm;
	
	p[34] = 0u;
	p[35] = 1u;
	p[18] = 255u;
	p[45] = 254u;
	p += 18;
	while (*p) {
		p += 9;
		while (*p != 254) {
			p += 9;
		}
		p[1] = 0u;
		while (*p != 255) {
			p -= 9;
		}
		p[9] += 2u;
		p += 9;
		while (*p) {
			p[0] += 254u;
			p[1] = 0u;
			p[6] = 0u;
			p[1] += p[8];
			p[6] += p[8];
			p[8] = p[1];
			p[1] = 0u;
			p[9] += 2u;
			p += 9;
		}
		p[0]--;
		while (*p) {
			p[0]--;
			p[-9]++;
			p -= 9;
		}
		p[0]--;
		p[1] = 1u;
		p++;
		while (*p) {
			p[1] = 1u;
			p++;
			while (*p) {
				p[7] += 2u;
				p += 7;
				while (*p) {
					p[0] += 254u;
					p[2] = 0u;
					p[1] = p[6];
					p[2] += p[6];
					p[6] = p[2];
					p[2] = 0u;
					p++;
					while (*p) {
						p[0] = 0u;
						p[-1] = 253u;
						p[0] = 0u;
						p[1] = 0u;
						p[2] = 0u;
						p[3] = 1u;
						p[1] = p[5];
						p[5] = 0u;
						p++;
						while (*p) {
							p[0]--;
							p[4]++;
							while (*p) {
								p[0]--;
								p[4]++;
								while (*p) {
									p[0]--;
									p[4]++;
									while (*p) {
										p[0]--;
										p[4]++;
										while (*p) {
											p[0]--;
											p[4]++;
											while (*p) {
												p[0]--;
												p[4]++;
												while (*p) {
													p[0]--;
													p[4]++;
													while (*p) {
														p[0]--;
														p[4]++;
														while (*p) {
															p[0]--;
															p[4]++;
															while (*p) {
																p[0]--;
																p[4] += 2u;
																p[-8] = 1u;
																p -= 8;
																while (*p) {
																	p[11]++;
																	p[0] = 0u;
																	p[1] = 0u;
																	p[0] += p[11];
																	p[1] += p[11];
																	p[11] = p[0];
																	p[0] = 1u;
																	p++;
																	if (*p) {
																		p[0] = 0u;
																		p[-1]--;
																	}
																	p[0] += p[-1];
																	p[-1] = 0u;
																	if (*p) {
																		p[0] = 0u;
																		p[8] = 1u;
																	}
																	p += 8;
																}
																p += 6;
																while (*p != 253) {
																	p -= 9;
																}
																p[6] = 0u;
																p[4] = 1u;
																p++;
															}
														}
													}
												}
											}
										}
									}
								}
							}
							p++;
						}
						p++;
						while (*p) {
							p[0]--;
							p--;
						}
						p[-3] = 0u;
						p[-2] = 0u;
						p[-1] = 0u;
						p[0] = 0u;
						p[1] = 0u;
						p -= 2;
					}
					p[8] += 2u;
					p += 8;
				}
				p[0]--;
				while (*p) {
					p[0]--;
					p[-9]++;
					p -= 9;
				}
				p[0]--;
				p[18] += 2u;
				p += 18;
				while (*p) {
					p[0] = 253u;
					p += 6;
					while (*p) {
						p[0]--;
						p[-3] = 25u;
						p -= 3;
						while (*p) {
							p[0]--;
							p[-11] = 1u;
							p -= 11;
							while (*p) {
								p[4]++;
								p[0] = 0u;
								p[1] = 0u;
								p[0] += p[4];
								p[1] += p[4];
								p[4] = p[0];
								p[0] = 1u;
								p++;
								if (*p) {
									p[0] = 0u;
									p[-1]--;
								}
								p[0] += p[-1];
								p[-1] = 0u;
								if (*p) {
									p[0] = 0u;
									p[8] = 1u;
								}
								p += 8;
							}
							p += 8;
							while (*p != 253) {
								p -= 9;
							}
							p += 3;
						}
						p[0] += 6u;
						while (*p) {
							p[0]--;
							p[-11] = 1u;
							p -= 11;
							while (*p) {
								p[5]++;
								p[0] = 0u;
								p[1] = 0u;
								p[0] += p[5];
								p[1] += p[5];
								p[5] = p[0];
								p[0] = 1u;
								p++;
								if (*p) {
									p[0] = 0u;
									p[-1]--;
								}
								p[0] += p[-1];
								p[-1] = 0u;
								if (*p) {
									p[0] = 0u;
									p[8] = 1u;
								}
								p += 8;
							}
							p += 8;
							while (*p != 253) {
								p -= 9;
							}
							p += 3;
						}
						p += 3;
					}
					p[-6] = 0u;
					p[3] += 2u;
					p += 3;
				}
				p[0]--;
				while (*p) {
					p[0]--;
					p[-9]++;
					p -= 9;
				}
				p[0]--;
				p[4] = 0u;
				p[10] = 10u;
				p[12] = 0u;
				p[11] = p[15];
				p[12] += p[15];
				p[15] = p[12];
				p[12] = 0u;
				p += 10;
				while (*p) {
					p[0]--;
					p[3] = 0u;
					p[2] = p[1];
					p[3] += p[1];
					p[1] = p[3];
					p[3] = 1u;
					p += 2;
					if (*p) {
						p[0] = 0u;
						p[1]--;
					}
					p[0] += p[1];
					p[1] = 0u;
					if (*p) {
						p[0] = 0u;
						p[-8]++;
					}
					p[-1]--;
					p -= 2;
				}
				p[1] = 0u;
				p -= 6;
				while (*p) {
					p[0] = 1u;
					p[14] += 2u;
					p += 14;
					while (*p) {
						p[0] += 254u;
						p[2] = 0u;
						p[1] = p[6];
						p[2] += p[6];
						p[6] = p[2];
						p[2] = 0u;
						p++;
						while (*p) {
							p[0] = 0u;
							p--;
							while (*p != 255) {
								p -= 9;
							}
							p[4] = 0u;
							p += 9;
							while (*p != 254) {
								p += 9;
							}
							p -= 8;
						}
						p[8] += 2u;
						p += 8;
					}
					p[0]--;
					while (*p) {
						p[0]--;
						p[-9]++;
						p -= 9;
					}
					p[0]--;
					p += 4;
					if (*p) {
						p[0] = 0u;
						p[-2] = 0u;
					}
				}
				p -= 2;
			}
			p += 7;
			while (*p != 254) {
				p += 9;
			}
			while (*p) {
				p++;
			}
			p[1] = 0u;
			p[0] += 50u;
			while (*p) {
				p[0] += 254u;
				p[-1] += 2u;
				p--;
			}
			p[0]--;
			while (*p) {
				p[0]--;
				p[-9]++;
				p -= 9;
			}
			p[0]--;
			p += 15;
			while (*p) {
				p[0]--;
				p -= 6;
				while (*p != 254) {
					p += 9;
				}
				while (*p) {
					p++;
				}
				p[-1] += 3u;
				p--;
				while (*p) {
					p[0] += 254u;
					p[-1] += 2u;
					p--;
				}
				p[0]--;
				while (*p) {
					p[0]--;
					p[-9]++;
					p -= 9;
				}
				p[0]--;
				p += 15;
			}
			p[-11] = 1u;
			p[-6] += 2u;
			p -= 6;
			while (*p) {
				p[0] += 254u;
				p[2] = 0u;
				p[1] = p[5];
				p[2] += p[5];
				p[5] = p[2];
				p[2] = 0u;
				p++;
				while (*p) {
					p[0] = 0u;
					p--;
					while (*p != 255) {
						p -= 9;
					}
					p[4] = 0u;
					p += 9;
					while (*p != 254) {
						p += 9;
					}
					p -= 8;
				}
				p[8] += 2u;
				p += 8;
			}
			p[0]--;
			while (*p) {
				p[0]--;
				p[-9]++;
				p -= 9;
			}
			p[0]--;
			p[3] = 1u;
			p += 4;
			while (*p) {
				p[0] = 0u;
				p[-3] = 0u;
				p[-1] = 0u;
				p += 5;
				while (*p != 254) {
					p += 9;
				}
				while (*p) {
					p++;
				}
				p[-1] += 2u;
				p--;
				while (*p) {
					p[0] += 254u;
					putchar(p[0]);
					p[0] = 0u;
					p[-1] += 2u;
					p--;
				}
				p[0]--;
				while (*p) {
					p[0]--;
					p[-9]++;
					p -= 9;
				}
				p[0]--;
				p += 4;
			}
			p--;
			while (*p) {
				p[0] = 0u;
				p[6] += 2u;
				p += 6;
				while (*p) {
					p[0] += 254u;
					p[6] = p[5];
					p[5] = 0u;
					p[9] += 2u;
					p += 9;
				}
				p[0]--;
				while (*p) {
					p[0]--;
					p[-9]++;
					p -= 9;
				}
				p[0]--;
				p += 3;
			}
			p -= 2;
		}
		p[9] += 10u;
		putchar(p[9]);
		p[9] = 0u;
		p[8] += 2u;
		p += 8;
		while (*p) {
			p[0] += 254u;
			p[1] = 0u;
			p[2] = 0u;
			p[1] += p[7];
			p[2] += p[7];
			p[7] = p[1];
			p[1] = 0u;
			p[3] = 0u;
			p[1] += p[8];
			p[3] += p[8];
			p[8] = p[1];
			p[1] = 0u;
			p += 3;
			while (*p) {
				p[0]--;
				p[7] = 0u;
				p[8] = 0u;
				p[-1]++;
				p[8] = 0u;
				p[7] = p[-1];
				p[8] += p[-1];
				p[-1] = p[8];
				p[8] = 1u;
				p += 7;
				if (*p) {
					p[0] = 0u;
					p[1]--;
				}
				p[0] += p[1];
				p[1] = 0u;
				if (*p) {
					p[0] = 0u;
					p[-9]++;
				}
				p -= 7;
			}
			p -= 11;
			while (*p) {
				p[0] = 0u;
				p[18] = 0u;
				p[19] = 0u;
				p[10]++;
				p[19] = 0u;
				p[18] = p[10];
				p[19] += p[10];
				p[10] = p[19];
				p[19] = 1u;
				p += 18;
				if (*p) {
					p[0] = 0u;
					p[1]--;
				}
				p[0] += p[1];
				p[1] = 0u;
				if (*p) {
					p[0] = 0u;
					p[-9]++;
				}
				p -= 18;
			}
			p[15] = p[16];
			p[16] = p[10];
			p[10] = 0u;
			p[17] += 2u;
			p += 17;
		}
		p[0] += 254u;
		p[2] = 0u;
		p[1] = p[-1];
		p[2] += p[-1];
		p[-1] = p[2];
		p[2] = 0u;
		p++;
		if (*p) {
			p[0] = 0u;
			p[-1] = 0u;
			p[8] = 254u;
		}
		p--;
		while (*p != 255) {
			p -= 9;
		}
	}
	p += 9;
	
	return EXIT_SUCCESS;
}
